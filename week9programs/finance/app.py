import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

from datetime import datetime
import pytz

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Get user cash balance
    q_user = db.execute("SELECT cash FROM users WHERE id = ? ;", session["user_id"])
    cash_bal = q_user[0]["cash"]

    stock_value = 0 # Sums the value of the user's purchased stock

    # The index page will sum up all of the user's shares to show only the unique symbols
    display_rows = db.execute("SELECT symbol,quantity FROM user_totals WHERE user_id = ? ORDER BY symbol ASC;", session["user_id"])
    for row in display_rows:
        stock_price = lookup(row["symbol"].upper())
        stock_price = stock_price["price"] # Holds the price of the stock the user wants to sell
        row["price"] = stock_price # Creates new key value pair

        total = stock_price * row["quantity"]
        stock_value += total
        row["total"] = total # Creates new key value pair to the current dictionary to be used to display on index.html

    return render_template("index.html", rows=display_rows, cash_bal=cash_bal, total=cash_bal+stock_value)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":

        symbol = request.form.get("symbol")
        row = lookup(symbol)
        if not symbol or row == None:
            return apology("invalid symbol")

        num_shares = request.form.get("shares")
        try:
            num_shares = int(num_shares) # Attempt to convert data type to int
            if num_shares < 1:
                return apology("not a positive integer")
        except:
            return apology("invalid number of shares")

        symbol = symbol.upper()

        # Retrieve user info (format: {'user_id': #})
        user_info = db.execute("SELECT * FROM users WHERE id = ?;", session["user_id"])

        # Check if user has sufficient funds for transaction
        if row["price"] * num_shares > user_info[0]["cash"]:
            return apology("insufficient funds")

        # Update the user's balance
        new_bal = user_info[0]["cash"] - (row["price"] * num_shares)
        db.execute("UPDATE users SET cash = ? WHERE id = ?;", new_bal, session["user_id"])

        # Update user's quantities
        q_shares = db.execute("SELECT quantity FROM user_totals WHERE user_id = ? AND symbol = ?;", session["user_id"], symbol)
        if len(q_shares) != 0:
            tot_shares = q_shares[0]["quantity"] # Existing stock
        else:
            tot_shares = 0 # New stock

        check_symbol_exists = db.execute("SELECT * FROM user_totals WHERE user_id = ? AND symbol = ?;", session["user_id"], symbol)

        if len(check_symbol_exists) == 0: # Row currently doesn't exist in user_totals table
            db.execute("INSERT INTO user_totals (user_id, symbol, quantity) VALUES (?, ?, ?);",
                        session["user_id"], symbol, num_shares)
        else: # Update the new value to the user_totals table
            tot_shares += num_shares
            db.execute("UPDATE user_totals SET quantity = ? WHERE user_id = ? AND symbol = ?;", tot_shares, session["user_id"], symbol)

        # Format the date and time based on Eastern time
        now = datetime.now(tz=pytz.timezone("America/New_York"))
        formatted_day = f"{now.year}/{now.month:02}/{now.day:02}"
        formatted_time = f"{now.hour:02}:{now.minute:02}"

        # Post transaction to transactions table
        db.execute("INSERT INTO transactions (date, time, user_id, symbol, quantity, price, status) VALUES (?, ?, ?, ?, ?, ?, ?);",
                   formatted_day, formatted_time, session["user_id"], symbol, num_shares, row["price"], "BUY")

        return redirect("/")

    else: # Request is GET
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    rows = db.execute("SELECT date,time,symbol,quantity,price,status FROM transactions WHERE user_id = ? ORDER BY date DESC, time DESC;", session["user_id"])
    return render_template("history.html", rows=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password")

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":

        symbol = request.form.get("symbol")
        row = lookup(symbol) # Get the dictionary returned
        if not symbol or row == None: # Empty request or if invalid symbol, lookup returns none
            return apology("invalid symbol")

        return render_template("quoted.html", row=row)

    else: # GET request
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        if not request.form.get("username"):
            return apology("must provide username")

        row = db.execute("SELECT * FROM users WHERE username = ?;", request.form.get("username"))
        if len(row) != 0:
            return apology("username already exists")

        if not request.form.get("password"):
            return apology("must provide password")

        if not request.form.get("confirmation"):
            return apology("must confirm password")

        if request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords do not match")

        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)",
                   request.form.get("username"), generate_password_hash(request.form.get("password")))

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":

        symbol = request.form.get("symbol")
        symbol = symbol.upper()
        shares_available = db.execute("SELECT symbol,quantity FROM user_totals WHERE user_id = ? AND symbol = ?;", session["user_id"], symbol)

        if len(shares_available) == 0:
            return apology("invalid symbol")

        num_shares = request.form.get("shares")
        try:
            num_shares = int(num_shares) # Attempt to convert data type to int
            if num_shares < 1:
                return apology("not a positive integer")
        except:
            return apology("invalid number of shares")

        if num_shares > shares_available[0]["quantity"]:
            return apology("invalid number of shares")

        price = lookup(symbol)
        price = price["price"] # Holds the price of the stock the user wants to sell

        current_bal = db.execute("SELECT cash FROM users WHERE id = ?;", session["user_id"])
        current_bal = current_bal[0]["cash"] # Holds the current cash balance of the user

        new_balance = current_bal + (price * num_shares)
        # Update the user's cash balance
        db.execute("UPDATE users SET cash = ? WHERE id = ?;", new_balance, session["user_id"])

        current_quantity = shares_available[0]["quantity"] - num_shares
        # Updates the user's amount of owned shares
        db.execute("UPDATE user_totals SET quantity = ? WHERE user_id = ? AND symbol = ?;", current_quantity, session["user_id"], symbol)

        # Format the date and time based on Eastern time
        now = datetime.now(tz=pytz.timezone("America/New_York"))
        formatted_day = f"{now.year}/{now.month:02}/{now.day:02}"
        formatted_time = f"{now.hour:02}:{now.minute:02}"

        # Post sell transaction to transactions table
        db.execute("INSERT INTO transactions (date, time, user_id, symbol, quantity, price, status) VALUES (?, ?, ?, ?, ?, ?, ?);",
                   formatted_day, formatted_time, session["user_id"], symbol, num_shares, price, "SELL")

        return redirect("/")

    else:

        rows = db.execute("SELECT symbol FROM user_totals WHERE user_id = ?;", session["user_id"])
        return render_template("sell.html", rows=rows)


# Personal touch that allows user to add funds
@app.route("/add_cash", methods=["GET", "POST"])
@login_required
def add_cash():
    """Adds user funds"""
    if request.method == "POST":

        cash_to_add = request.form.get("add_cash")
        try:
            cash_to_add = int(cash_to_add) # Attempt to convert user data to an integer
        except:
            return apology("invalid amount")

        if cash_to_add < 1: # Reject any value less than 1
            return apology("invalid amount")

        cash_original = db.execute("SELECT cash FROM users WHERE id = ?;", session["user_id"])
        cash_original = cash_original[0]["cash"] # Get only the numerical value

        db.execute("UPDATE users SET cash = ? WHERE id = ?;", cash_original+cash_to_add, session["user_id"])

        return redirect("/")

    else:
        return render_template("add_funds.html")

