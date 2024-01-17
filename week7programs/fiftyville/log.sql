-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Check the crime scene report description
-- on the day of July 28, 2021 at Humphrey Street
SELECT
    description
FROM
    crime_scene_reports
WHERE
    (1=1)
    AND year = 2021
    AND month = 7
    AND day = 28
    AND street = 'Humphrey Street';


-- Read the interviews of the witnessess
SELECT
    name
    ,transcript
FROM
    interviews
WHERE
    (1=1)
    AND year = 2021
    AND month = 7
    AND day = 28;


-- Analyze Ruth's interview response by checking the bakery security logs
-- for cars that exited between 10:15 - 10:30
SELECT
    activity
    ,license_plate
    ,minute
    ,hour
FROM
    bakery_security_logs
WHERE
    (1=1)
    AND year = 2021
    AND month = 7
    AND day = 28
    AND activity = 'exit'
    AND hour = 10
    AND minute >= 15
    AND minute <= 30;


-- Analyze Eugene's interview response by checking the ATM transactions
-- at Leggett Street for withdrawals
SELECT
    account_number
FROM
    atm_transactions
WHERE
    (1=1)
    AND year = 2021
    AND month = 7
    AND day = 28
    AND atm_location = 'Leggett Street'
    AND transaction_type = 'withdraw';


-- Analyze Raymond's interview response by checking phone calls whose duration
-- is less than or equal to one minute
SELECT
    caller
    ,receiver
    ,duration
FROM
    phone_calls
WHERE
    (1=1)
    AND year = 2021
    AND month = 7
    AND day = 28
    AND duration <= 60;


-- Analyze further Raymond's interview response by checking the earliest flight out
-- of Fiftyville tomorrow, July 29, 2021
SELECT
    *
FROM
    airports
    JOIN flights ON flights.origin_airport_id = airports.id
WHERE
    (1=1)
    AND year = 2021
    AND month = 7
    AND day = 29
    AND full_name LIKE '%Fiftyville%'
ORDER BY
    hour ASC
    ,minute ASC
LIMIT 1;


-- Get a suspect name, phone number, passport number and license plate
-- by checking various parameters specified in comments
-- WHERE predicates are based off of previous queries
-- This query narrows down the people to one individual, Bruce
SELECT
    DISTINCT name
    ,phone_number
    ,people.passport_number
    ,BSL.license_plate
FROM
    people
    JOIN bank_accounts ON bank_accounts.person_id = people.id
    JOIN bakery_security_logs BSL ON BSL.license_plate = people.license_plate

    -- These joins are used to identify the passengers on the earliest flight out of Fiftyville
    JOIN airports ON airports.id = flights.origin_airport_id
    JOIN flights ON flights.origin_airport_id = airports.id
    JOIN passengers ON passengers.flight_id = flights.id
WHERE
    (1=1)
    -- Checks bank account numbers that match people that withdrew on July 28, 2021
    AND bank_accounts.account_number IN (
        SELECT
            account_number
        FROM
            atm_transactions
        WHERE
            (1=1)
            AND year = 2021
            AND month = 7
            AND day = 28
            AND atm_location = 'Leggett Street'
            AND transaction_type = 'withdraw'
    )
    -- Checks phone numbers of individuals that had a less than or equal to 60 second phone call
    AND people.phone_number IN (
        SELECT
            caller
        FROM
            phone_calls
        WHERE
            (1=1)
            AND year = 2021
            AND month = 7
            AND day = 28
            AND duration <= 60
    )
    -- Checks license plates of individuals that left within 10:15 - 10:30
    AND people.license_plate IN (
        SELECT
            license_plate
        FROM
            bakery_security_logs
        WHERE
            (1=1)
            AND year = 2021
            AND month = 7
            AND day = 28
            AND activity = 'exit'
            AND hour = 10
            AND minute >= 15
            AND minute <= 30
    )
    -- Checks the passengers on the flight out of Fiftyville tomorrow
    AND people.passport_number IN (
        SELECT
            passengers.passport_number
        FROM
            airports
            JOIN flights ON flights.origin_airport_id = airports.id
            JOIN passengers ON passengers.flight_id = flights.id
        WHERE
            (1=1)
            AND year = 2021
            AND month = 7
            AND day = 29
            AND flights.hour = 8
            AND flights.minute = 20
            AND full_name LIKE '%Fiftyville%'
    );


-- Find out where the first flight out of Fiftyville tomorrow is heading out to
SELECT
    airports.city
FROM
    airports
    JOIN flights ON flights.destination_airport_id = airports.id
WHERE
    (1=1)
    AND year = 2021
    AND month = 7
    AND day = 29
    AND flights.hour = 8
    AND flights.minute = 20
    AND flights.origin_airport_id IN ( -- Confirm origin airport is Fiftyville
        SELECT
            DISTINCT flights.origin_airport_id
        FROM
            airports
            JOIN flights ON flights.origin_airport_id = airports.id
        WHERE
            (1=1)
            AND year = 2021
            AND month = 7
            AND day = 29
            AND full_name LIKE '%Fiftyville%'
    );


-- Assuming Bruce is the suspect, find information on the caller
SELECT
    people.name
FROM
    phone_calls
    JOIN people ON people.phone_number = phone_calls.receiver
WHERE
    (1=1)
    AND year = 2021
    AND month = 7
    AND day = 28
    AND duration <= 60
    AND caller = '(367) 555-5533'; -- Using Bruce's phone number
