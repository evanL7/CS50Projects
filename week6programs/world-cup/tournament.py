# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 10000


def main():
    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    # Read teams into memory from file
    with open(sys.argv[1]) as f:
        reader = csv.DictReader(f)
        for row in reader:
            teams.append({"team": row["team"], "rating": int(row["rating"])})

    counts = {}
    # Simulate N tournaments and keep track of win counts
    for i in range(N):
        team_name = simulate_tournament(teams)
        if (team_name not in counts):  # Checks if the winning team is not already in our dictionary
            counts[team_name] = 0
        counts[team_name] += 1  # Increments the number of wins of the winning team by one

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    current = teams
    while len(current) != 1:  # Loop until current is left with one team
        current = simulate_round(current)
    return current[0]["team"]  # Returns the winning team name


if __name__ == "__main__":
    main()
