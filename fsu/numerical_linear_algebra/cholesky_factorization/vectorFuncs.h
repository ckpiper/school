extern void print(vector<int> v);
extern void print(vector<float> v);
extern void print(vector<double> v);

extern void print(vector<vector<int>> A);
extern void print(vector<vector<float>> A);
extern void print(vector<vector<double>> A);

extern int isRectangular(vector<vector<int>> A);
extern int isRectangular(vector<vector<float>> A);
extern int isRectangular(vector<vector<double>> A);

extern vector<int> add(vector<int> v, vector<int> w);
extern vector<float> add(vector<float> v, vector<float> w);
extern vector<double> add(vector<double> v, vector<double> w);

extern vector<vector<int>> add(vector<vector<int>> A, vector<vector<int>> B);
extern vector<vector<float>> add(vector<vector<float>> A, vector<vector<float>> B);
extern vector<vector<double>> add(vector<vector<double>> A, vector<vector<double>> B);

extern vector<int> subtract(vector<int> v, vector<int> w);
extern vector<float> subtract(vector<float> v, vector<float> w);
extern vector<double> subtract(vector<double> v, vector<double> w);

extern vector<vector<int>> subtract(vector<vector<int>> A, vector<vector<int>> B);
extern vector<vector<float>> subtract(vector<vector<float>> A, vector<vector<float>> B);
extern vector<vector<double>> subtract(vector<vector<double>> A, vector<vector<double>> B);

extern int innnerProduct(vector<int> x, vector<int> y);
extern float innnerProduct(vector<float> x, vector<float> y);
extern double innnerProduct(vector<double> x, vector<double> y);
extern int dotProduct(vector<int> x, vector<int> y);
extern float dotProduct(vector<float> x, vector<float> y);
extern double dotProduct(vector<double> x, vector<double> y);

extern vector<int> product(vector<vector<int>> A, vector<int> v);
extern vector<float> product(vector<vector<float>> A, vector<float> v);
extern vector<double> product(vector<vector<double>> A, vector<double> v);

extern vector<int> product(vector<int> v, vector<vector<int>> B);
extern vector<float> product(vector<float> v, vector<vector<float>> B);
extern vector<double> product(vector<double> v, vector<vector<double>> B);

extern vector<vector<int>> product(vector<vector<int>> A, vector<vector<int>> B);
extern vector<vector<float>> product(vector<vector<float>> A, vector<vector<float>> B);
extern vector<vector<double>> product(vector<vector<double>> A, vector<vector<double>> B);

extern vector<vector<int>> outerProduct(vector<int> x, vector<int> y);
extern vector<vector<float>> outerProduct(vector<float> x, vector<float> y);
extern vector<vector<double>> outerProduct(vector<double> x, vector<double> y);

extern float vectorPNorm(float p, vector<int> x);
extern float vectorPNorm(float p, vector<float> x);
extern double vectorPNorm(double p, vector<double> x);

extern float vectorInfNorm(vector<int> x);
extern float vectorInfNorm(vector<float> x);
extern double vectorInfNorm(vector<double> x);

extern float matrix1Norm(vector<vector<int>> A);
extern float matrix1Norm(vector<vector<float>> A);
extern double matrix1Norm(vector<vector<double>> A);

extern float matrixInfNorm(vector<vector<int>> A);
extern float matrixInfNorm(vector<vector<float>> A);
extern double matrixInfNorm(vector<vector<double>> A);

extern float matrixFNorm(vector<vector<int>> A);
extern float matrixFNorm(vector<vector<float>> A);
extern double matrixFNorm(vector<vector<double>> A);

extern vector<float> vectorGenerator(int maxInt, int n, float decimal);
extern vector<double> vectorGenerator(int maxInt, int n, double decimal);

extern vector<vector<float>> matrixGenerator(int maxInt, int n, int k, float decimal);
extern vector<vector<double>> matrixGenerator(int maxInt, int n, int k, double decimal);
