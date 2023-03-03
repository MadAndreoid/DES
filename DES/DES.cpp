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
/// <typeparam name="n">The number of bits that compose the bitset</typeparam>
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
bitset<48>* generate_key(bitset<64> key)
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

	bitset<48>keys[16];

    bitset<24>leftKey;
    {

        bitset<24>rightKey;
        {

            bitset<48>perm_key(0);
            {

                for (int i = 0; i < 56; i++)
                {
                    perm_key[i] = key[pc1[i] - 1];
                }



                for (int i = 0; i < 24; i++)
                {
                    rightKey[i] = perm_key[i];
					leftKey[i] = perm_key[27 + i];
				}
            }

			for (int i = 0; i < 16; i++)
			{
				switch (i)
				{
				case 0:
				case 1:
				case 8:
				case 15:
					leftKey = left_shift(leftKey);
					rightKey = left_shift(leftKey);
				default:
					leftKey = twice_left_shift(leftKey);
					rightKey = twice_left_shift(rightKey);
					break;
				}

			}

        }
    }
    return keys;
}

template<size_t n>
bitset<n> Des(bitset<64>*keys)
{
#pragma region ]TABLES[

	int initial_permutation[64] = {
	58,50,42,34,26,18,10,2,
	60,52,44,36,28,20,12,4,
	62,54,46,38,30,22,14,6,
	64,56,48,40,32,24,16,8,
	57,49,41,33,25,17,9,1,
	59,51,43,35,27,19,11,3,
	61,53,45,37,29,21,13,5,
	63,55,47,39,31,23,15,7
	};
	// The expansion table
	int expansion_table[48] = {
	32,1,2,3,4,5,4,5,
	6,7,8,9,8,9,10,11,
	12,13,12,13,14,15,16,17,
	16,17,18,19,20,21,20,21,
	22,23,24,25,24,25,26,27,
	28,29,28,29,30,31,32,1
	};
	// The substitution boxes. The should contain values
	// from 0 to 15 in any order.
	int substition_boxes[8][4][16] = {
		{
			14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
			0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
			4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
			15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13
		},
		{
			15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
			3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
			0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
			13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9
		},
		{
			10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
			13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
			13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
			1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12
		},
		{
			7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
			13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
			10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
			3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14
		},
		{
			2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
			14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
			4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
			11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3
		},
		{
			12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
			10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
			9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
			4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13
		},
		{
			4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
			13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
			1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
			6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12
		},
		{
			13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
			1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
			7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
			2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11
		}
	};
	// The permutation table
	int permutation_tab[32] = {
	16,7,20,21,29,12,28,17,
	1,15,23,26,5,18,31,10,
	2,8,24,14,32,27,3,9,
	19,13,30,6,22,11,4,25
	};
	// The inverse permutation table
	int inverse_permutation[64] = {
	40,8,48,16,56,24,64,32,
	39,7,47,15,55,23,63,31,
	38,6,46,14,54,22,62,30,
	37,5,45,13,53,21,61,29,
	36,4,44,12,52,20,60,28,
	35,3,43,11,51,19,59,27,
	34,2,42,10,50,18,58,26,
	33,1,41,9,49,17,57,25
	};

#pragma endregion


	return;
}

#pragma endregion



int main()
{
	string strKey;
	string strPt;
    
	while (true)
	{
		cout << "Insert Plain Text:(8char)" << endl;
		cin >> strPt;

		if (strPt.length() > 8)
		{
			cout << "Too many char" << endl;
			continue;
		}
		break;
	}

	while (true)
	{
		cout << "Insert Key(8char):" << endl;
		cin >> strKey;

		if (strKey.length() > 8)
		{
			cout << "Too many char" << endl;
			continue;
		}
		break;

	}

	int desLenght = strPt.length() * 8;
	bitset<desLenght>Des();

    //
}
