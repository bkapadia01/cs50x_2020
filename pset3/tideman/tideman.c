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
bool locked_cycle(int start, int end);

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
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
            printf("%i-%i--%d...\n", ranks[i], ranks[j], preferences[ranks[i]][ranks[j]]);
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                printf("IJ: %i, %i\n",  pairs[pair_count].winner, pairs[pair_count].loser);
                pair_count++;
            }
                
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                printf("JI: %i, %i\n",  pairs[pair_count].winner, pairs[pair_count].loser);
                pair_count++;
            }
            else
            {
                continue;
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i + 1 ; j < pair_count; j++)
        {
            int strengthPairIJ = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
            int strengthPairJI = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            printf("<<<< %i - %i>>>> \n", strengthPairIJ, strengthPairJI);
            if (strengthPairJI > strengthPairIJ)
            {
                printf("swappp\n");
                pair temp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temp;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO

    for (int i = 0; i < pair_count; i++)
    {
        int win = pairs[i].winner;
        int loss = pairs[i].loser;
        printf("%i win == %i loss \n", win, loss);

        if (!locked_cycle(win, loss))
        {
            locked[win][loss] = true;
            printf("locked cycle!! win-loss %i - %i \n", win, loss);
        }
    }
    return;
}

bool locked_cycle(int start, int end)
{
    if (start == end)
    {
        printf("%i start == %i end \n", start, end);
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        printf("check locked: %i-start %i-end %i-i\n", start, end, i);

        if (locked[end][i] && locked_cycle(start, i))
        {
            printf("locked!! %i-start %i-end %i-i\n", start, end, i);
            return true;
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{

    // TODO
    bool lead;

    for (int i = 0; i < candidate_count; i++)
    {
        lead = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                lead = false;
                printf("locked j/i but lead = false \n");
            }
        }
        if (lead)
        {
            printf("%s\n", candidates[i]);
        }
    }

    return;
}

