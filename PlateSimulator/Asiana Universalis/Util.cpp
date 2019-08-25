#include "Util.h"

float3 Util::HSV2RGB(double H, double S, double V) {
	double r = 0, g = 0, b = 0;
	double h = H;
	double s = S;
	double v = V;
	if (h > 400)
	{
		h = 400;
	}
	else if (h < 0)
	{
		h = 0;
	}

	if (s > 1.00)
	{
		s = 1.00;
	}
	else if (s < 0)
	{
		s = 0;
	}
	
	if (v > 1.00)
	{
		v = 1.00;
	}
	else if (v < 0)
	{
		v = 0;
	}

	if (s == 0)
	{
		r = v;
		g = v;
		b = v;
	}
	else
	{
		int i;
		double f, p, q, t;

		if (h == 360)
			h = 0;
		else
			h = h / 60;

		i = (int)trunc(h);
		f = h - i;

		p = v * (1.0 - s);
		q = v * (1.0 - (s * f));
		t = v * (1.0 - (s * (1.0 - f)));

		switch (i)
		{
		case 0:
			r = v;
			g = t;
			b = p;
			break;

		case 1:
			r = q;
			g = v;
			b = p;
			break;

		case 2:
			r = p;
			g = v;
			b = t;
			break;

		case 3:
			r = p;
			g = q;
			b = v;
			break;

		case 4:
			r = t;
			g = p;
			b = v;
			break;

		default:
			r = v;
			g = p;
			b = q;
			break;
		}

	}

	return float3((unsigned char)(r * 255), (unsigned char)(g * 255), (unsigned char)(b * 255));

	/*
	switch (sec)
	{
	case 0:
	{
		return (unsigned char)(r * 255);
	}
	case 1:
	{
		return (unsigned char)(g * 255);
	}
	case 2:
	{
		return (unsigned char)(b * 255);
	}
	}*/
}

double Util::PP2DIR(double x, double y)
{
	if (x > 0)
	{
		if (y >= 0)
		{
			return atan(y/x);
		}

		return atan(y/x) + 360;
	}
	else if (x < 0)
	{
		return atan(y / x) + 180;
	}
	if (y > 0)
	{
		return 90;
	}
	
	return 270;
}