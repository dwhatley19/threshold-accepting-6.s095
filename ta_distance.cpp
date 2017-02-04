#include "ta.h"
using namespace std;

double distance(pii a, pii b)
{
    return sqrt((a.A-b.A)*(a.A-b.A) + (a.B-b.B)*(a.B-b.B));
}

double distance(piii x, piii y)
{
    pii a = x.A;
    pii b = y.A;
    return sqrt((a.A-b.A)*(a.A-b.A) + (a.B-b.B)*(a.B-b.B));
}

vector<int> locations;
vector<piii> coords;

void print(vector<int> v)
{
    for(int i = 0; i < v.size(); ++i) cout << v[i] << ' ';
    cout << endl;
}

// PRECONDITION: i < j
double lin_2_opt(double cost, vector<piii> path, int i, int j, vector<piii> *new_path)
{
    int n = path.size();
    cost -= (distance(path[i], path[(i + 1) % n]) + distance(path[j], path[(j + 1) % n]));
    cost += (distance(path[i], path[j]) + distance(path[(i + 1) % n], path[(j + 1) % n]));

    *new_path = path;
    vector<int> copy_locations = locations;
    for(int x = i + 1; x <= j; ++x) {
        locations[path[i + j + 1 - x].B] = copy_locations[(*new_path)[x].B];
        (*new_path)[x] = path[i + j + 1 - x];
    }

    //print(locations);

    return cost;
}

void Problem::solve(string filename, int N)
{
    ifstream fin((filename + ".txt").c_str());
    ofstream fout((filename + "d.out").c_str());

    int k;
    vector<piii> path;
    double length = 0;

    while(fin >> k) {
        double x, y;
        fin >> x >> y;

        coords.push_back(piii(pii(x, y), k - 1));
        if(k > 1) length += distance(coords[k - 1], coords[k - 2]);
    }

    path = coords;
    int n = coords.size();
    length += distance(coords[0], coords[n - 1]);

    // Generate length matrix & sort by individual city.
    vector<pdii> lengths(n);
    for(int i = 0; i < n; ++i) {
        locations.push_back(i);
        for(int j = 0; j < n; ++j) {
            if(i != j) lengths.push_back(pdii(distance(coords[i], coords[j]), ii(i, j)));
        }
    }
    sort(lengths.begin(), lengths.end());
    int num_conn = lengths.size();

    for(int i = 0; i < thresholds.size(); ++i) {
        cout << thresholds[i] << endl;
        for(int j = 0; j < N; ++j) {
            // we don't want to include city j itself
            vector<piii> new_path;
            double new_length;

            int rand1 = rand() % (num_conn/3), rand2 = rand() % (num_conn/3);
            int one = locations[lengths[rand1].B.A], two = locations[lengths[rand2].B.B];

            if(one < two) new_length = lin_2_opt(length, path, one, two, &new_path);
            else new_length = lin_2_opt(length, path, two, one, &new_path);

            if(length > new_length - thresholds[i]) {
                length = new_length;
                path = new_path;
            }
        }
        //fout << "after " << thresholds[i] << " length == " << length << endl;
    }

    double final_length = 0;
    ofstream fout2("att532d_trace.out");
    for(int i = 0; i < n - 1; ++i) {
        fout2 << final_length << " + ";
        final_length += distance(path[i], path[i + 1]);
        fout2 << distance(path[i], path[i + 1]) << " = " << final_length << endl;
    }
    fout << final_length + distance(path[0], path[n - 1]) << endl;
    for(int i = 0; i < n; ++i) fout << '(' << path[i].A.A << "," << path[i].A.B << ") ";
    fout << endl;
}

int main(int argc, char **argv)
{
    /*ifstream fin("solutions.txt");

    string s1, s2;
    int sol;
    while(fin >> s1 >> s2 >> sol) {
        solve(s1);
    }*/

    srand(time(NULL));
    cout << "hi\n";

    Problem p;
    p.solve(string(argv[2]), atoi(argv[1]));
}
