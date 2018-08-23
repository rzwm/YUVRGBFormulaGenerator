#include <iostream>
#include <numeric>
#include <algorithm>

void generateFormula_origin(double W_R, double W_G, double W_B, double U_max, double V_max, int Scale)
{
	std::cout << "Y->[0, 255] U->[-255U_max, 255U_max] V->[-255V_max, 255V_max]" << std::endl;
	std::cout << "Y =  " 
		<< W_R << "R + " 
		<< W_G << "G + " 
		<< W_B << "B" << std::endl;

	std::cout << "U = -" 
		<< std::abs((W_R * U_max) / (1 - W_B)) << "R - "
		<< std::abs((W_G * U_max) / (1 - W_B)) << "G + " 
		<< U_max << "B" << std::endl;

	std::cout << "V =  " 
		<< V_max << "R - " 
		<< std::abs((W_G * V_max) / (1 - W_R)) << "G - "
		<< std::abs((W_B * V_max) / (1 - W_R)) << "B" << std::endl;

	std::cout << "R = Y + " 
		<< (1 - W_R) / V_max << "V" << std::endl;

	std::cout << "G = Y - " 
		<< (W_B * (1 - W_B)) / (U_max * W_G) << "U - "
		<< (W_R * (1 - W_R)) / (V_max * W_G) << "V" << std::endl;

	std::cout << "B = Y + " 
		<< (1 - W_B) / U_max << "U" << std::endl;

	if (Scale != 0)
	{
		std::cout << "Y = (" 
			<< (int)std::round(W_R * Scale) << "R + " 
			<< (int)std::round(W_G * Scale) << "G + " 
			<< (int)std::round(W_B * Scale) << "B + "
			<< Scale / 2 << ") / "
			<< Scale << std::endl;

		std::cout << "U = (-" 
			<< (int)std::round(std::abs((W_R * U_max * Scale) / (1 - W_B))) << "R - "
			<< (int)std::round(std::abs((W_G * U_max * Scale) / (1 - W_B))) << "G + "
			<< (int)std::round(U_max * Scale) << "B + "
			<< Scale / 2 << ") / " 
			<< Scale << std::endl;

		std::cout << "V = (" 
			<< (int)std::round(V_max * Scale) << "R - " 
			<< (int)std::round(std::abs((W_G * V_max * Scale) / (1 - W_R))) << "G - "
			<< (int)std::round(std::abs((W_B * V_max * Scale) / (1 - W_R))) << "B + "
			<< Scale / 2 << ") / "
			<< Scale << std::endl;

		std::cout << "R = (" << Scale << "Y + "
			<< (int)std::round(((1 - W_R) * Scale) / V_max) << "V + " 
			<< Scale / 2 << ") / "
			<< Scale << std::endl;

		std::cout << "G = (" << Scale << "Y - "
			<< (int)std::round((W_B * (1 - W_B) * Scale) / (U_max * W_G)) << "U - "
			<< (int)std::round((W_R * (1 - W_R) * Scale) / (V_max * W_G)) << "V + "
			<< Scale / 2 << ") / "
			<< Scale << std::endl;

		std::cout << "B = (" << Scale << "Y + "
			<< (int)std::round(((1 - W_B) * Scale) / U_max) << "U + " 
			<< Scale / 2 << ") / "
			<< Scale << std::endl;
	}
}

void generateFormula_studio(double W_R, double W_G, double W_B, double U_max, double V_max, int Scale)
{
	std::cout << "Y->[16, 235] U->[16, 240] V->[16, 240]" << std::endl;
	std::cout << "Y =  "
		<< W_R * 219 / 255 << "R + "
		<< W_G * 219 / 255 << "G + "
		<< W_B * 219 / 255 << "B + 16" << std::endl;

	std::cout << "U = -"
		<< std::abs((W_R * 112) / ((1 - W_B) * 255)) << "R - "
		<< std::abs((W_G * 112) / ((1 - W_B) * 255)) << "G + "
		<< 112.0 / 255.0 << "B + 128" << std::endl;

	std::cout << "V =  "
		<< 112.0 / 255.0 << "R - "
		<< std::abs((W_G * 112) / ((1 - W_R) * 255)) << "G - "
		<< std::abs((W_B * 112) / ((1 - W_R) * 255)) << "B + 128" << std::endl;

	std::cout << "R = "
		<< 255.0 / 219.0 << "(Y - 16) + "
		<< ((1 - W_R) * 255) / 112 << "(V - 128)" << std::endl;

	std::cout << "G = "
		<< 255.0 / 219.0 << "(Y - 16) - "
		<< (W_B * (1 - W_B) * 255) / (W_G * 112) << "(U - 128) - "
		<< (W_R * (1 - W_R) * 255) / (W_G * 112) << "(V - 128)" << std::endl;

	std::cout << "B = "
		<< 255.0 / 219.0 << "(Y - 16) + "
		<< ((1 - W_B) * 255) / 112 << "(U - 128)" << std::endl;

	if (Scale != 0)
	{
		std::cout << "Y = ("
			<< (int)std::round(W_R * 219 * Scale / 255) << "R + "
			<< (int)std::round(W_G * 219 * Scale / 255) << "G + "
			<< (int)std::round(W_B * 210 * Scale / 255) << "B + 16 + "
			<< Scale / 2 << ") / "
			<< Scale << std::endl;

		std::cout << "U = (-"
			<< (int)std::round(std::abs((W_R * 112 * Scale) / ((1 - W_B) * 255))) << "R - "
			<< (int)std::round(std::abs((W_G * 112 * Scale) / ((1 - W_B) * 255))) << "G + "
			<< (int)std::round(112.0 * Scale / 255.0) << "B + 128 + "
			<< Scale / 2 << ") / "
			<< Scale << std::endl;

		std::cout << "V = ("
			<< (int)std::round(112.0 * Scale / 255.0) << "R - "
			<< (int)std::round(std::abs((W_G * 112 * Scale) / ((1 - W_R) * 255))) << "G - "
			<< (int)std::round(std::abs((W_B * 112 * Scale) / ((1 - W_R) * 255))) << "B + 128 + " 
			<< Scale / 2 << ") / "
			<< Scale
			<< std::endl;

		std::cout << "R = ("
			<< (int)std::round(255.0 * Scale / 219.0) << "(Y - 16) + "
			<< (int)std::round(((1 - W_R) * 255 * Scale) / 112) << "(V - 128) + "
			<< Scale / 2 << ") / "
			<< Scale << std::endl;

		std::cout << "G = ("
			<< (int)std::round(255.0 * Scale / 219.0) << "(Y - 16) - "
			<< (int)std::round((W_B * (1 - W_B) * 255 * Scale) / (W_G * 112)) << "(U - 128) - "
			<< (int)std::round((W_R * (1 - W_R) * 255 * Scale) / (W_G * 112)) << "(V - 128) + "
			<< Scale / 2 << ") / "
			<< Scale << std::endl;

		std::cout << "B = ("
			<< (int)std::round(255.0 * Scale / 219.0) << "(Y - 16) + "
			<< (int)std::round(((1 - W_B) * 255 * Scale) / 112) << "(U - 128) + "
			<< Scale / 2 << ") / "
			<< Scale << std::endl;
	}
}

void generateFormula_full(double W_R, double W_G, double W_B, double U_max, double V_max, int Scale)
{
	std::cout << "Y->[0, 255] U->[0, 255] V->[0, 255]" << std::endl;
	std::cout << "Y =  "
		<< W_R << "R + "
		<< W_G << "G + "
		<< W_B << "B" << std::endl;

	std::cout << "U = -"
		<< std::abs((W_R * 0.5) / ((1 - W_B))) << "R - "
		<< std::abs((W_G * 0.5) / ((1 - W_B))) << "G + "
		<< 0.5 << "B + 128" << std::endl;

	std::cout << "V =  "
		<< 0.5 << "R - "
		<< std::abs((W_G * 0.5) / ((1 - W_R))) << "G - "
		<< std::abs((W_B * 0.5) / ((1 - W_R))) << "B + 128" << std::endl;

	std::cout << "R = "
		<< "Y + "
		<< (1 - W_R) * 2 << "(V - 128)" << std::endl;

	std::cout << "G = "
		<< "Y - "
		<< (W_B * (1 - W_B) * 2) / (W_G) << "(U - 128) - "
		<< (W_R * (1 - W_R) * 2) / (W_G) << "(V - 128)" << std::endl;

	std::cout << "B = "
		<< "Y + "
		<< ((1 - W_B) * 2) << "(U - 128)" << std::endl;

	if (Scale != 0)
	{
		std::cout << "Y =  ("
			<< (int)std::round(W_R * Scale) << "R + "
			<< (int)std::round(W_G * Scale) << "G + "
			<< (int)std::round(W_B * Scale) << "B + "
			<< Scale / 2 << ") / "
			<< Scale
			<< std::endl;

		std::cout << "U = (-"
			<< (int)std::round(std::abs((W_R * 0.5 * Scale) / ((1 - W_B)))) << "R - "
			<< (int)std::round(std::abs((W_G * 0.5 * Scale) / ((1 - W_B)))) << "G + "
			<< (int)std::round(0.5 * Scale) << "B + 128 + "
			<< Scale / 2 << ") / "
			<< Scale
			<< std::endl;

		std::cout << "V =  ("
			<< (int)std::round(0.5 * Scale) << "R - "
			<< (int)std::round(std::abs((W_G * 0.5 * Scale) / ((1 - W_R)))) << "G - "
			<< (int)std::round(std::abs((W_B * 0.5 * Scale) / ((1 - W_R)))) << "B + 128 + "
			<< Scale / 2 << ") / "
			<< Scale
			<< std::endl;

		std::cout << "R = ("
			<< Scale
			<< "Y + "
			<< (int)std::round((1 - W_R) * Scale * 2) << "(V - 128) + "
			<< Scale / 2 << ") / "
			<< Scale
			<< std::endl;

		std::cout << "G = ("
			<< Scale
			<< "Y - "
			<< (int)std::round((W_B * (1 - W_B) * 2 * Scale) / (W_G)) << "(U - 128) - "
			<< (int)std::round((W_R * (1 - W_R) * 2 * Scale) / (W_G)) << "(V - 128) + "
			<< Scale / 2 << ") / "
			<< Scale
			<< std::endl;

		std::cout << "B = ("
			<< Scale
			<< "Y + "
			<< (int)std::round(((1 - W_B) * 2 * Scale)) << "(U - 128) + "
			<< Scale / 2 << ") / "
			<< Scale
			<< std::endl;
	}
}

void generateFormula(double W_R, double W_G, double W_B, double U_max, double V_max, int Scale)
{
	generateFormula_origin(W_R, W_G, W_B, U_max, V_max, Scale);
	std::cout << std::endl;
	generateFormula_studio(W_R, W_G, W_B, U_max, V_max, Scale);
	std::cout << std::endl;
	generateFormula_full(W_R, W_G, W_B, U_max, V_max, Scale);
	std::cout << std::endl;
}

int main()
{
	std::cout.setf(std::ios::right);
	std::cout.width(8);
	std::cout.fill(' ');
	std::cout.precision(6);
	std::cout.setf(std::ios::showpoint);
	std::fixed(std::cout);

	std::cout << "Welcome to YUV and RGB conversion formula generator!" << std::endl << std::endl;;
	std::cout << "Which formula do you want to generate?" << std::endl;
	std::cout << "->0: BT.601" << std::endl;
	std::cout << "->1: BT.709" << std::endl;
	std::cout << "->Other: Customize" << std::endl;

	int index = 0;
	std::cout << "Please select: " << std::endl;
	std::cin >> index;
	if (!std::cin.good())
	{
		index = -1;
		std::cin.clear();
	}

	double W_R = 0.299;
	double W_G = 0.587;
	double W_B = 0.114;
	double U_max = 0.436;
	double V_max = 0.615;
	int Scale = 0;

	if (0 == index) // BT.601
	{
		W_R = 0.299;
		W_G = 0.587;
		W_B = 0.114;
		U_max = 0.436;
		V_max = 0.615;
	}
	else if (1 == index)
	{
		W_R = 0.2126;
		W_G = 0.7152;
		W_B = 0.0722;
		U_max = 0.436;
		V_max = 0.615;
	}
	else
	{
		do 
		{
			std::cout << "Please input W_R(weight of R channel) and W_B(weight of B channel)" << std::endl;
			std::cout << "Their's range are (0, 1) and (W_B + W_R)'s range is also (0, 1): " << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin >> W_R;
			if (!std::cin.good())
			{
				continue;
			}

			std::cin >> W_B;
			if (!std::cin.good())
			{
				continue;
			}
		} while (W_R <= 0.0 || W_B <= 0.0 || W_R + W_B >= 1.0 || !std::cin.good());

		W_G = 1.0 - W_R - W_B;

		do
		{
			std::cout << "Please input U_max(max value of U) and V_max(max value of V)" << std::endl;
			std::cout << "Their's range are (0, 1): " << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin >> U_max;
			if (!std::cin.good())
			{
				continue;
			}

			std::cin >> V_max;
			if (!std::cin.good())
			{
				continue;
			}
		} while (U_max <= 0.0 || V_max <= 0.0 || U_max >= 1.0f || V_max >= 1.0 || !std::cin.good());
		std::cout << std::endl;
	}

	std::cout << std::endl;
	std::cout << "Do you want output fixed point formula the same time? " << std::endl;
	std::cout << "->0: NO!" << std::endl;
	std::cout << "->Other: YES!" << std::endl;

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Please select: " << std::endl;
	int scale_index = 0;
	std::cin >> scale_index;
	if (!std::cin.good())
	{
		scale_index = -1;
		std::cin.clear();
	}

	if (0 != scale_index)
	{
		do
		{
			std::cout << "Please input Scale(an integer to convert float to fixed point): " << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin >> Scale;
			if (!std::cin.good())
			{
				continue;
			}
		} while (Scale <= 0 || !std::cin.good());
	}

	std::cout << std::endl;
	if (0 == index)
	{
		std::cout << "BT.601" << std::endl;
	}
	else if (1 == index)
	{
		std::cout << "BT.709" << std::endl;
	}
	else
	{
		std::cout << "Customize" << std::endl;
	}
	std::cout << "Parameters: " << std::endl;
	std::cout << "W_R:   " << W_R << std::endl;
	std::cout << "W_G:   " << W_G << std::endl;
	std::cout << "W_B:   " << W_B << std::endl;
	std::cout << "U_max: " << U_max << std::endl;
	std::cout << "V_max: " << V_max << std::endl;
	if (0 != Scale)
	{
		std::cout << "Scale: " << Scale << std::endl;
	}
	std::cout << std::endl;

	generateFormula(W_R, W_G, W_B, U_max, V_max, Scale);
	std::cout << "Done!" << std::endl;

	return 0;
}
