#include "ta.h"
using namespace std;

double distance(pii a, pii b)
{
    return sqrt((a.A-b.A)*(a.A-b.A) + (a.B-b.B)*(a.B-b.B));
}

// PRECONDITION: i < j
double Problem::lin_2_opt(double cost, vector<pii> path, int i, int j, vector<pii> *new_path)
{
    int n = path.size();
    cost -= (distance(path[i], path[(i + 1) % n]) + distance(path[j], path[(j + 1) % n]));
    cost += (distance(path[i], path[j]) + distance(path[(i + 1) % n], path[(j + 1) % n]));

    *new_path = path;
    for(int x = i + 1; x <= j; ++x) {
        (*new_path)[x] = path[i + j + 1 - x];
    }

    return cost;
}

void Problem::solve(string filename, int nb)
{
    ifstream fin((filename + ".txt").c_str());
    ofstream fout((filename + ".out").c_str());

    int k;
    vector<pii> path;
    double length = 0;

    while(fin >> k) {
        double x, y;
        fin >> x >> y;

        coords.push_back(pii(x, y));
        if(k > 1) length += distance(coords[k - 1], coords[k - 2]);
    }

    path = coords;
    int n = coords.size();
    length += distance(coords[0], coords[n - 1]);

    // Generate length matrix & sort by individual city.
    vector<vector<pdi> > lengths(n);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            lengths[i].push_back(pdi(distance(coords[i], coords[j]), j));
        }
        sort(lengths[i].begin(), lengths[i].end());
    }

    for(int i = 0; i < thresholds.size(); ++i) {
        for(int j = 0; j < n; ++j) {
            // we don't want to include city j itself
            for(int k = 1; k <= nb + 1; ++k) {
                vector<pii> new_path;
                double new_length;

                if(j < lengths[j][k].B) new_length = lin_2_opt(length, path, j, lengths[j][k].B, &new_path);
                else new_length = lin_2_opt(length, path, lengths[j][k].B, j, &new_path);

                if(length > new_length - thresholds[i]) {
                    length = new_length;
                    path = new_path;
                }
            }
        }
        //fout << "after " << thresholds[i] << " length == " << length << endl;
    }

    double final_length = 0;
    ofstream fout2("att532_trace.out");
    for(int i = 0; i < n - 1; ++i) {
        fout2 << final_length << " + ";
        final_length += distance(path[i], path[i + 1]);
        fout2 << distance(path[i], path[i + 1]) << " = " << final_length << endl;
    }
    fout << final_length + distance(path[0], path[n - 1]) << endl;
    for(int i = 0; i < n; ++i) fout << '(' << path[i].A << "," << path[i].B << ") ";
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

    Problem p;
    p.solve(string(argv[2]), atoi(argv[1]));
}
