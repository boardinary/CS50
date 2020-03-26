#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void merge(int l, int m, int r);
void sort(int l, int r);
bool check_cycle(int cand1, int cand2);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Linear search for name in candidates
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            // Name found in candidates
            ranks[rank] = i;

            return true;
        }
    }

    // Name is not found in candidates
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Build preferences array
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;

        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0, k = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > 0 && preferences[i][j] > preferences[j][i])
            {
                pair_count++;
                pairs[k].winner = i;
                pairs[k].loser = j;
                k++;
            }

        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Create temporary pair
    pair sorted[pair_count];

    sort(0, pair_count);
    return;
}

// Recursion sort function
void sort(int l, int r)
{
    int m;

    // Base case that left index must be less than right index in order to have something to sort
    if (l < r)
    {
        m = (l + r) / 2;
        sort(l, m);
        sort(m + 1, r);

        merge(l, m, r);
    }
    else
    {
        return;
    }
}

// merge two pairs that have been sorted in order
void merge(int l, int m, int r)
{
    // Create temp pair
    pair sorted[pair_count];

    // Initialize indicies
    int i, j, k;

    for (i = l, j = m + 1, k = l; i <= m && j <= r; k++)
    {
        if (preferences[pairs[i].winner][pairs[i].loser] >= preferences[pairs[j].winner][pairs[j].loser])
        {
            sorted[k] = pairs[i];
            i++;
        }
        else
        {
            sorted[k] = pairs[j];
            j++;
        }
    }

    // Assign remaining values before m
    while (i <= m)
    {
        sorted[k] = pairs[i];
        k++;
        i++;
    }

    // Assign remaining values after m
    while (j <= r)
    {
        sorted[k] = pairs[j];
        k++;
        j++;
    }

    // assign sorted values to pairs
    for (i = l; i <= r; i++)
    {
        pairs[i] = sorted[i];
    }

}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Loop through pairs and lock them in if a cycle is not present
    for (int i = 0, j = 0; i < pair_count; i++)
    {

        if (check_cycle(pairs[i].loser, pairs[i].winner) == false)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;

        }

    }

    return;
}

// Check to see if cycle exists

bool check_cycle(int cand1, int cand2)
{
    // Base case
    if (locked[cand1][cand2] == true)
    {
        return true;
    }

    // Loop through candidates to see if one beat cand2
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][cand2] == true)
        {
            // Recursively check if path back to cand1 exists. Return true if check_cycle is true.
            if (check_cycle(cand1, i) == true)
            {
                return true;
            }
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{

    int winner[candidate_count];
    int winner_count;

    for (int i = 0, j = 0, k = 0; i < candidate_count && j < candidate_count;)
    {
        // Rule out candidates with edges pointing at them
        if (locked[i][j] == true)
        {
            j++;
            i = 0;
        }

        // Record candidate with no edges pointing at them into winner array
        else if (i == candidate_count - 1)
        {
            winner[k] = j;
            k++;
            i = 0;
            j++;
            winner_count = k;
        }
        i++;
    }

    printf("\n");

    for (int i = 0; i < winner_count; i++)
    {
        printf("%s\n", candidates[winner[i]]);
    }

    return;
}

