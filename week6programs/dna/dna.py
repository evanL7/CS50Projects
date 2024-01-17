import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Missing command line arguments")
        return

    # Read database file into a variable
    people = list()
    csvfilename = sys.argv[1]
    with open(csvfilename) as csvf:
        csvcontents = csv.DictReader(csvf)

        for i in csvcontents:
            people.append(i)  # Note: sequence values stored as a string, need to change to int

    # Read DNA sequence file into a variable
    txtfilename = sys.argv[2]
    with open(txtfilename) as txtf:
        txtcontents = txtf.read()

    # Find longest match of each STR in DNA sequence
    sequences = list()  # Stores the names of the potential sequences, excluding the person's name
    for i in people[0]:  # Arbitrarily choose the first person
        if i != "name":
            sequences.append(i)

    count_sequence = dict()  # Stores a dictionary containing the sequence as the key and the longest number of occurrences as the value
    for i in sequences:
        count = longest_match(txtcontents, i)
        count_sequence[i] = count  # Creates the key-value pair

    # Check database for matching profiles
    for i in range(len(people)):
        count = 0  # Resets the counter after each iteration
        for j in range(len(sequences)):  # Iterates through the potential sequences
            current_person = people[i]  # Gets the potential individual
            current_sequence = sequences[j]  # Gets the current sequence being analyzed
            if count_sequence[current_sequence] == int(current_person[current_sequence]):  # Checks if the provided sequence matches the current individual
                count += 1
                continue
            else:  # If the current person's sequence doesn't match for one sequence, the individual is not a match at all and we go to the next person
                break

        if count == len(sequences):  # Check the number of matches found if they are the same, we found the matching DNA
            print(current_person["name"])  # Prints the matching person's name
            return

    print("No match")  # Exiting the loop implies no matches
    return


def longest_match(sequence: str, subsequence: str):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
