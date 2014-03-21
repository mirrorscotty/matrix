#ifndef VECTOR_H
#define VECTOR_H

/**
 * @struct vector
 * @brief A data structure for a vector of abitrary length
 * @var vector::v
 * A pointer to the raw data
 * @var vector::length
 * The number of components in the vector
 */
typedef struct {
    double *v;
    int length;
} vector;

vector* CreateVector(int);
void DestroyVector(vector*);
vector* linspaceV(double, double, int);
vector* CopyVector(vector*);
//double valV(vector*, int);
void setvalV(vector*, int, double);
int len(vector*);

void PrintVector(vector*);

vector* addV(vector*, vector*);
vector* subtractV(vector*, vector*);
double dotV(vector*, vector*);
vector* scalarmultV(double, vector*);
int equalV(vector*, vector*);

/**
 * @brief macro to retrieve the value of a particular component of a vector
 * @param VECTOR The vector to pull the value from
 * @param INDEX The index of the component
 */
#define valV(VECTOR, INDEX) (VECTOR)->v[(INDEX)]

#endif

