/*
██████╗ ███████╗███████╗    ███████╗██╗███╗   ███╗██╗   ██╗██╗      █████╗ ████████╗██╗ ██████╗ ███╗   ██╗
██╔══██╗██╔════╝██╔════╝    ██╔════╝██║████╗ ████║██║   ██║██║     ██╔══██╗╚══██╔══╝██║██╔═══██╗████╗  ██║
██║  ██║█████╗  ███████╗    ███████╗██║██╔████╔██║██║   ██║██║     ███████║   ██║   ██║██║   ██║██╔██╗ ██║
██║  ██║██╔══╝  ╚════██║    ╚════██║██║██║╚██╔╝██║██║   ██║██║     ██╔══██║   ██║   ██║██║   ██║██║╚██╗██║
██████╔╝███████╗███████║    ███████║██║██║ ╚═╝ ██║╚██████╔╝███████╗██║  ██║   ██║   ██║╚██████╔╝██║ ╚████║
╚═════╝ ╚══════╝╚══════╝    ╚══════╝╚═╝╚═╝     ╚═╝ ╚═════╝ ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝

    By Andrea Marinacci

*/

#pragma region ]INCLUDES[

#include <iostream>
#include <bitset>
#include <cstdlib>
#include <stdlib.h>
#include <math.h>

#pragma endregion

#pragma region ]OTHER STORIES[

using namespace std;

#pragma endregion

#pragma region ]FUNCTIONES[

/// <summary>
/// Cast a string to bitset v0.1
/// </summary>
/// <typeparam name="n">The number of bits taht compose the bitset</typeparam>
/// <param name="str">(The string that u want to cast)</param>
/// <returns> (Returns the string casted in a bitset)</returns>
template <size_t n>
bitset<n> string_to_Bitset(string str)
{
    string sr;

    for (int i = 0; i < str.length(); i++)
    {
        bitset<8> c(str[i]);
        sr += c.to_string();
    }

    bitset<n> result(sr);

    return result;
}

template <size_t n>
bitset<n> bitset_Xor(bitset<n> bits1, bitset<n> bits2)
{
    return bitset<n>(bits1 ^= bits2);
}

template <size_t n>
bitset<n> left_shift(bitset<n> toshift)
{
    bitset<1> first(toshift[0]);

    bitset<n> result(toshift << 1);

    result[n - 1] = first[0];

    return result;
}

template <size_t n>
bitset<n> twice_left_shift(bitset<n> toshift)
{
    toshift = left_shift(toshift);

    return left_shift(toshift);

}
template <size_t n>
bitset<n>* generate_key(bitset<n> key)
{
#pragma region ]PERMUTATION CHOICE[

    int pc1[56] = {
57,	49,	41,	33,	25,	17,	9,
1,	58,	50,	42,	34,	26,	18,
10,	2,	59,	51,	43,	35, 27,
19,	11,	3,	60,	52,	44,	36,
63,	55,	47,	39,	31,	23,	15,
7,	62,	54,	46,	38,	30,	22,
14,	6,	61,	53,	45,	37,	29,
21,	13,	5,	28,	20,	12,	4 };

    int pc2[48] = {
14,	17,	11,	24,	1,	5,
3,	28,	15,	6,	21,	10,
23,	19,	12,	4,	26,	8,
16,	7,	27,	20,	13,	2,
41,	52,	31,	37,	47,	55,
30,	40,	51,	45,	33,	48,
44,	49,	39,	56,	34,	53,
46,	42,	50,	36,	29,	32 };

#pragma endregion

    bitset<n / 2>leftKey;
    {

        bitset<n / 2>rightKey;
        {

            bitset<n>perm_key(0);
            {

                for (int i = 0; i < 56; i++)
                {
                    perm_key[i] = key[pc1[i] - 1];
                }



                for (int i = 0; i < n / 2; i++)
                {
                    rightKey[i] = perm_key[i];
                }

                for (int i = 0; i < n / 2; i++)
                {
                    leftKey[i] = perm_key[27 + i];
                }
            }

        }
    }
    return key;
}

#pragma endregion



int main()
{
    bitset<64>* keys;
    keys = generate_key(bitset<64>(1));
    //
}
