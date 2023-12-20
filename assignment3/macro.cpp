#include <iostream>
#include <vector>
#include <stack>
#include <map>
using namespace std;
struct var_def
{
    string var_name;
    string var_mapping;
};

struct func_def
{
    string func_name;
    int param_num;
    int order_of_func_tot;
    map<int, string> signs;       // store index->string
    map<int, int> order_of_param; // store index of param in value->index of input param in func
};

vector<var_def *> var_vec;
vector<func_def *> func_vec;
string tot;
int main()
{
    string tmp_s;
    while (getline(cin, tmp_s))
    {
        tot += tmp_s;
        tot += "\n";
    }

    for (int i = 0; i < tot.size(); i++)
    {
        int next_whitespace = min(tot.find_first_of(' ', i), min(tot.find_first_of('\n', i), tot.find_first_of('\t', i)));
        string next_s = tot.substr(i, next_whitespace - i);
        // cout << next_s << endl;
        if (next_s == "#define")
        {

            i = next_whitespace + 1;
            next_whitespace = min(tot.find_first_of(' ', i), min(tot.find_first_of('\n', i), tot.find_first_of('\t', i)));
            string next_s = tot.substr(i, next_whitespace - i);
            // cout << next_s << endl;
            if (next_s.find('(') != next_s.npos)
            {
                // function definition
                func_def *tmp_func = new func_def;
                tmp_func->func_name = next_s;

                stack<char> stac;
                map<string, int> params;
                stac.push('(');
                int params_num_cnt = 0;
                int param_idx_start = next_whitespace + 1;
                while (!stac.empty())
                {
                    i = next_whitespace + 1;
                    next_whitespace = min(tot.find_first_of(' ', i), min(tot.find_first_of('\n', i), tot.find_first_of('\t', i)));
                    string next_s = tot.substr(i, next_whitespace - i);
                    // cout << next_s << endl;
                    if (stac.size() == 1 && next_s == ")")
                    {
                        stac.pop();
                        string tmp_param = tot.substr(param_idx_start, i - 1 - param_idx_start);
                        // cout << "tmp_param:" << tmp_param <<endl;
                        params[tmp_param] = params_num_cnt;
                        params_num_cnt++;
                        param_idx_start = next_whitespace + 1;
                        tmp_func->param_num = params_num_cnt;
                        /*check duplication for define*/
                        for (int j = 0; j < func_vec.size(); j++)
                        {
                            if (func_vec[j]->func_name == tmp_func->func_name && func_vec[j]->param_num == tmp_func->param_num)
                            {
                                cout << "ERROR DUP\n";
                                return 0;
                            }
                        }
                        func_vec.push_back(tmp_func);
                    }
                    else if (next_s == "," && stac.size() == 1)
                    {
                        string tmp_param = tot.substr(param_idx_start, i - 1 - param_idx_start);
                        // cout << "tmp_param:" << tmp_param <<endl;
                        params[tmp_param] = params_num_cnt;
                        params_num_cnt++;
                        param_idx_start = next_whitespace + 1;
                    }
                    else if (next_s == "(")
                    {
                        stac.push('(');
                    }
                    else if (next_s == ")")
                    {
                        stac.pop();
                    }
                } // function macro end
                // function macro value start

                int order_of_func = 0;
                while (true)
                {
                    if (tot[next_whitespace] == '\n')
                    {
                        i = next_whitespace;
                        tmp_func->order_of_func_tot = order_of_func;
                        break;
                    }

                    i = next_whitespace + 1;
                    next_whitespace = min(tot.find_first_of(' ', i), min(tot.find_first_of('\n', i), tot.find_first_of('\t', i)));
                    string next_s = tot.substr(i, next_whitespace - i);
                    // cout << next_s << endl;
                    if (params.find(next_s) != params.end()) // find corresponding paramater
                    {
                        int origin_idx = params[next_s];
                        tmp_func->order_of_param[order_of_func] = origin_idx;
                        order_of_func++;
                    }
                    else
                    {
                        tmp_func->signs[order_of_func] = next_s;
                        order_of_func++;
                    }
                }
            }
            else
            {
                // variable definition
                var_def *tmp_var = new var_def;
                tmp_var->var_name = next_s;

                i = next_whitespace + 1;
                next_whitespace = min(tot.find_first_of(' ', i), min(tot.find_first_of('\n', i), tot.find_first_of('\t', i)));
                string next_s = tot.substr(i, next_whitespace - i);
                tmp_var->var_mapping = next_s;
                /*check duplicatio for variable*/
                for (int j = 0; j < var_vec.size(); j++)
                {
                    if (var_vec[j]->var_name == tmp_var->var_name)
                    {
                        cout << "ERROR DUP\n";
                        return 0;
                    }
                }

                var_vec.push_back(tmp_var);
                i = next_whitespace;
            }
        }
        else if (next_s == "#undef")
        {
            // TODO
            i = next_whitespace + 1;
            next_whitespace = min(tot.find_first_of(' ', i), min(tot.find_first_of('\n', i), tot.find_first_of('\t', i)));
            string next_s = tot.substr(i, next_whitespace - i);
            // undef a variable
            if (next_s.find('(') == next_s.npos)
            {
                int found_define = 0;
                for (int j = 0; j < var_vec.size(); j++)
                {
                    if (var_vec[j]->var_name == next_s)
                    {
                        var_vec.erase(var_vec.begin() + j);
                        found_define = 1;
                        break;
                    }
                }
                if (!found_define)
                {
                    cout << "ERROR NFOUND\n";
                    return 0;
                }
                i = next_whitespace;
            }
            // undef a function
            else
            {
                string func_name_tmp = next_s;
                stack<char> stac;
                //map<int, string> params;
                stac.push('(');
                int params_num_cnt = 0;
                int param_idx_start = next_whitespace + 1;
                while (!stac.empty())
                {
                    i = next_whitespace + 1;
                    next_whitespace = min(tot.find_first_of(' ', i), min(tot.find_first_of('\n', i), tot.find_first_of('\t', i)));
                    string next_s = tot.substr(i, next_whitespace - i);
                    if (stac.size() == 1 && next_s == ")")
                    {
                        stac.pop();
                        if (i <= param_idx_start)
                        {
                            cout << "ERROR NFOUND\n";
                            break;
                        }
                        string tmp_param = tot.substr(param_idx_start, i - 1 - param_idx_start);
                        params_num_cnt++;
                        param_idx_start = next_whitespace + 1;

                        // check whether function is defined
                        int found_def = 0;
                        for (int j = 0; j < func_vec.size(); j++)
                        {
                            if (func_vec[j]->func_name == func_name_tmp && func_vec[j]->param_num == params_num_cnt)
                            { // same function name and parameter count
                                func_vec.erase(func_vec.begin()+j);
                                found_def = 1;
                                break;
                            }
                        }
                        if (!found_def)
                        { // If not find definition, print nfound
                            cout << "ERROR NFOUND\n";
                        }
                    }
                    else if (next_s == "," && stac.size() == 1)
                    {
                        string tmp_param = tot.substr(param_idx_start, i - 1 - param_idx_start);
                        // cout << "param_num: " << params_num_cnt << "tmp_param: " << tmp_param << endl;
                        params_num_cnt++;
                        param_idx_start = next_whitespace + 1;
                    }
                    else if (next_s == "(")
                    {
                        stac.push('(');
                    }
                    else if (next_s == ")")
                    {
                        stac.pop();
                    }
                }
                i = next_whitespace;
            }
        }
        else
        { // TODO
            /*variable normal*/
            if (next_s.find('(') == next_s.npos)
            {
                int found_define = 0;
                for (int j = 0; j < var_vec.size(); j++)
                {
                    if (var_vec[j]->var_name == next_s)
                    {
                        cout << var_vec[j]->var_mapping;
                        found_define = 1;
                        break;
                    }
                }
                if (!found_define)
                {
                    cout << next_s;
                }
                i = next_whitespace;
            }
            /*function normal*/
            else
            {
                string func_name_tmp = next_s;
                stack<char> stac;
                map<int, string> params;
                stac.push('(');
                int params_num_cnt = 0;
                int param_idx_start = next_whitespace + 1;
                while (!stac.empty())
                {
                    i = next_whitespace + 1;
                    next_whitespace = min(tot.find_first_of(' ', i), min(tot.find_first_of('\n', i), tot.find_first_of('\t', i)));
                    string next_s = tot.substr(i, next_whitespace - i);
                    if (stac.size() == 1 && next_s == ")")
                    {
                        stac.pop();
                        if (i <= param_idx_start)
                        {
                            cout << func_name_tmp << ")";
                            break;
                        }
                        string tmp_param = tot.substr(param_idx_start, i - 1 - param_idx_start);
                        
                        params[params_num_cnt] = tmp_param;
                        // cout << "param_num: " << params_num_cnt << "tmp_param: " << tmp_param << endl;
                        params_num_cnt++;
                        param_idx_start = next_whitespace + 1;

                        // TODO: check whether function is defined
                        int found_def = 0;
                        for (int j = 0; j < func_vec.size(); j++)
                        {
                            if (func_vec[j]->func_name == func_name_tmp && func_vec[j]->param_num == params_num_cnt)
                            { // same function name and parameter count

                                for (int t = 0; t < func_vec[j]->order_of_func_tot; t++)
                                {
                                    // cout << "t: " << t << endl;
                                    if (func_vec[j]->order_of_param.find(t) == func_vec[j]->order_of_param.end())
                                    {
                                        cout << func_vec[j]->signs[t];
                                    }
                                    else
                                    {
                                        cout << params[func_vec[j]->order_of_param[t]];
                                    }
                                }
                                found_def = 1;
                                break;
                            }
                        }
                        if (!found_def)
                        { // If not find definition, print whole function
                            cout << func_name_tmp;
                            for (int j = 0; j < params_num_cnt - 1; j++)
                            {
                                cout << params[j] << ",";
                            }
                            cout << params[params_num_cnt - 1] << ")";
                        }
                    }
                    else if (next_s == "," && stac.size() == 1)
                    {
                        string tmp_param = tot.substr(param_idx_start, i - 1 - param_idx_start);
                        params[params_num_cnt] = tmp_param;
                        // cout << "param_num: " << params_num_cnt << "tmp_param: " << tmp_param << endl;
                        params_num_cnt++;
                        param_idx_start = next_whitespace + 1;
                    }
                    else if (next_s == "(")
                    {
                        stac.push('(');
                    }
                    else if (next_s == ")")
                    {
                        stac.pop();
                    }
                }
                i = next_whitespace;
            }
        }
    }
}