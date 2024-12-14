#include "flag_parsers.h"

void ParseStatus(const vector<string> &phrases, Request &parsed_request, int &pos)
{
    // verify that something appears after this, and that it is an integer
    if (phrases.size() <= (pos + 1))
        throw std::invalid_argument("--status is missing a required following integer argument.");

    try
    {
        int status;
        status = stoi(phrases[pos + 1]);
        parsed_request.set_status(status);
    }
    catch (...)
    {
        throw std::invalid_argument("The argument to --status must be an integer.");
    }

    pos += 2;
}

void ParseVCount(const vector<string> &phrases, Request &parsed_request, int &pos)
{
    // verify that something appears after this, and that it is an integer
    if (phrases.size() <= (pos + 1))
        throw std::invalid_argument("--vcount is missing a required following integer argument.");

    try
    {
        int vcount;
        vcount = stoi(phrases[pos + 1]);
        parsed_request.set_vcount(vcount);
    }
    catch (...)
    {
        throw std::invalid_argument("The argument to --vcount must be an integer.");
    }

    pos += 2;
}

void ParseVSize(const vector<string> &phrases, Request &parsed_request, int &pos)
{
    // verify that something appears after this, and that it is an integer
    if (phrases.size() <= (pos + 1))
        throw std::invalid_argument("--vsize is missing a required following integer argument.");

    try
    {
        int vsize;
        vsize = stoi(phrases[pos + 1]);
        parsed_request.set_vsize(vsize);
    }
    catch (...)
    {
        throw std::invalid_argument("The argument to --vsize must be an integer.");
    }

    pos += 2;
}

void ParseTopK(const vector<string> &phrases, Request &parsed_request, int &pos)
{
    // verify that something appears after this, and that it is an integer
    if (phrases.size() <= (pos + 1))
        throw std::invalid_argument("--topk is missing a required following integer argument.");

    try
    {
        int topk;
        topk = stoi(phrases[pos + 1]);
        parsed_request.set_topk(topk);
    }
    catch (...)
    {
        throw std::invalid_argument("The argument to --topk must be an integer.");
    }

    pos += 2;
}

void ParseKeys(const vector<string> &phrases, Request &parsed_request, int &pos)
{
    // verify that the number of vectors has been specified earlier in the query,
    // as it is required to appear before the --keys flag
    int v_count = parsed_request.get_vcount();
    if (v_count == 0)
        throw std::invalid_argument("a non zero --vcount must be provided before --keys in query.");

    // verify that we have at least as many more phrases as we expect to have keys
    if (phrases.size() <= (pos + v_count))
        throw std::invalid_argument("the number of --keys provided must match the value of --vcount.");

    // parse all the keys and update parsed request
    vector<int> keys;
    try
    {
        for (int i = pos + 1; i <= pos + v_count; i++)
        {
            keys.push_back(stoi(phrases[i]));
        }
    }
    catch (...)
    {
        throw std::invalid_argument("All --key values must be integers.");
    }
    parsed_request.set_keys(keys);

    pos += v_count + 1;
}

void ParseVector(const vector<string> &phrases, Request &parsed_request, int &pos)
{
    // verify that the size of vectors has been specified earlier in the query,
    // as it is required to appear before the --vector flag
    int v_size = parsed_request.get_vsize();
    if (v_size == 0)
        throw std::invalid_argument("a non zero --vsize must be provided before --vector in query.");

    // verify that we have at least as many more phrases as we expect to have doubles
    if (phrases.size() <= (pos + v_size))
        throw std::invalid_argument("the number of doubles provided must match the value of --vsize.");

    // parse all the keys and update parsed request
    vector<double> v;
    try
    {
        for (int i = pos + 1; i <= pos + v_size; i++)
        {
            v.push_back(stod(phrases[i]));
        }
    }
    catch (...)
    {
        throw std::invalid_argument("All --vector elements must be doubles. An incomplete vector might have been sent.");
    }
    parsed_request.get_vectors_ref().push_back(v);

    pos += v_size + 1;
}