#include "Map.h"

void Map::KEY(unsigned int k)
{
	switch (k)
	{
		case SDLK_q:
		{
			MMD_ = 0;
			break;
		}
		case SDLK_w:
		{
			MMD_ = 1;
			break;
		}
		case SDLK_e:
		{
			MMD_ = 2;
			break;
		}
		case SDLK_r:
		{
			MMD_ = 3;
			break;
		}
		default:
			break;
	}
	return;
}




void Map::INIT()
{
	m_util = new Util;
	srand((unsigned int)time(NULL));

	m_data.INIT();

	for (int a = 0; a < Map::MAP_W; a++)
	{
		for (int b = 0; b < Map::MAP_H; b++)
		{
			Map::GRP_RECT[a][b].R = rand() % 255;
			Map::GRP_RECT[a][b].G = rand() % 255;
			Map::GRP_RECT[a][b].B = rand() % 255;
			Map::GRP_RECT[a][b].A = true;
		}
	}
	int t = 1;
	for (int a,b; t < m_data.MAX_PLATE; t++)
	{
		a = rand() % Map::MAP_W;
		b = rand() % Map::MAP_H;
		Map::GRP_RECT[a][b].PLATE_TYPE = t;
		Map::GRP_RECT[a][b].PLATE_H = 10.0;
		Map::GRP_RECT[a][b].PLATE_P = Map::GRP_RECT[a][b].PLATE_TYPE * 10;
		Map::GRP_RECT[a][b].GEO_H = 1.0;
		for (int w = 0; w < 8; w++)
		{
			Map::GRP_RECT[a][b].PLATE_W[0] = m_data.PLATE_W[Map::GRP_RECT[a][b].PLATE_TYPE][0] * 0.50;
			Map::GRP_RECT[a][b].PLATE_W[1] = m_data.PLATE_W[Map::GRP_RECT[a][b].PLATE_TYPE][0] * 0.50;
		}
	}


	PHY_ALL = PHY_CRS + PHY_RGT + PHY_STR + PHY_BCK;

	MMD_H.SET(-20, 20);
	MMD_GH.SET(0, 10);
	MMD_P.SET(0, 15);

	return;
}

void Map::STEP()
{
	//OutputDebugStringA(std::to_string(Map::GRP_RECT[60][60].PLATE_H).c_str());
	//OutputDebugStringA("\n");

	unsigned int a, b, w;
	int c, d;
	double e, f, g;
	unsigned int av;
	for (a = 0; a < Map::MAP_W; a++)
	{
		for (b = 0; b < Map::MAP_H; b++)
		{
			AVG_H += Map::GRP_RECT[a][b].PLATE_H;
		}
	}
	AVG_H /= Map::MAP_W * Map::MAP_H;
	for (a = 0; a < Map::MAP_W; a++)
	{
		for (b = 0; b < Map::MAP_H; b++)
		{
			DIT_H += pow(Map::GRP_RECT[a][b].PLATE_H-AVG_H,2);
		}
	}
	DIT_H /= Map::MAP_W * Map::MAP_H;
	for (a = 0; a < Map::MAP_W; a++)
	{
		for (b = 0; b < Map::MAP_H; b++)
		{
			if (Map::GRP_RECT[a][b].PLATE_H < 0)
			{
				Map::GRP_RECT[a][b].PLATE_TYPE = 0;
				Map::GRP_RECT[a][b].PLATE_H = 0;
			}

			if (Map::GRP_RECT[a][b].PLATE_H * Map::GRP_RECT[a][b].PLATE_P > 10.0)
			{
				//PLATE2GEO
				e = Map::GRP_RECT[a][b].PLATE_H / 2.0;
				e = e * atan(Map::GRP_RECT[a][b].PLATE_P) / M_PI_4;

				Map::GRP_RECT[a][b].PLATE_H -= 0.01;
				Map::GRP_RECT[a][b].GEO_H += 0.01;
			}
			
			if (Map::GRP_RECT[a][b].PLATE_TYPE ==  0 && Map::GRP_RECT[a][b].GEO_H > 20.0)
			{
				//GEO DOWN
				Map::GRP_RECT[a][b].GEO_H -= 0.015;
			}

			if (Map::GRP_RECT[a][b].PLATE_TYPE > 0 && Map::GRP_RECT[a][b].A)
			{
				Map::GRP_RECT[a][b].PLATE_W[0] = m_data.PLATE_W[Map::GRP_RECT[a][b].PLATE_TYPE][0];
				Map::GRP_RECT[a][b].PLATE_W[1] = m_data.PLATE_W[Map::GRP_RECT[a][b].PLATE_TYPE][1];

				Map::GRP_RECT[a][b].A = false;

				f = m_util->PP2DIR(Map::GRP_RECT[a][b].PLATE_W[0], Map::GRP_RECT[a][b].PLATE_W[1]);// make direction;

				for (w = 0; w < 8; w++)
				{
					if (f >= w * 45 && f < w * 45 + 45)
					{
						e = (f / 45) - a;
						Map::GRP_RECT[a][b].PLATE_MOVE[w] += (1 - b) * (PHY_STR / PHY_ALL) * 0.01;
						Map::GRP_RECT[a][b].PLATE_MOVE[(w + 1 + 8) % 8] += b * (PHY_STR / PHY_ALL)* 0.01;

						Map::GRP_RECT[a][b].PLATE_MOVE[(w - 1 + 8) % 8] += (1 - b) * (PHY_CRS / PHY_ALL)* 0.01;
						Map::GRP_RECT[a][b].PLATE_MOVE[(w + 2 + 8) % 8] += b * (PHY_CRS / PHY_ALL)* 0.01;

						Map::GRP_RECT[a][b].PLATE_MOVE[(w - 2 + 8) % 8] += (1 - b) * (PHY_RGT / PHY_ALL)* 0.01;
						Map::GRP_RECT[a][b].PLATE_MOVE[(w + 3 + 8) % 8] += b * (PHY_RGT / PHY_ALL)* 0.01;

						Map::GRP_RECT[a][b].PLATE_MOVE[(w - 3 + 8) % 8] += (1 - b) * (PHY_BCK / PHY_ALL)* 0.01;
						Map::GRP_RECT[a][b].PLATE_MOVE[(w + 4 + 8) % 8] += b * (PHY_BCK / PHY_ALL)* 0.01;
					}
				}
			}




			for (w = 0; w < 4; w++)
			{
				e = min(Map::GRP_RECT[a][b].PLATE_MOVE[w], Map::GRP_RECT[a][b].PLATE_MOVE[w + 4]);
				Map::GRP_RECT[a][b].PLATE_MOVE[w] -= e;
				Map::GRP_RECT[a][b].PLATE_MOVE[w + 4] -= e;
			}

			for (w = 0; w < 8; w++)
			{

				c = (a + W[w][0] + Map::MAP_W) % Map::MAP_W;
				d = b + W[w][1];

				if (Map::GRP_RECT[a][b].PLATE_MOVE[w] < 0)
				{
					Map::GRP_RECT[a][b].PLATE_MOVE[(w + 4) % 8] -= Map::GRP_RECT[a][b].PLATE_MOVE[w];
					Map::GRP_RECT[a][b].PLATE_MOVE[w] = 0;
				}
				if (Map::GRP_RECT[a][b].PLATE_P > Map::GRP_RECT[c][d].PLATE_P)
				{
					e = Map::GRP_RECT[a][b].PLATE_P - Map::GRP_RECT[c][d].PLATE_P;
					Map::GRP_RECT[a][b].PLATE_MOVE[w] += e;
				}
				if (Map::GRP_RECT[a][b].PLATE_TYPE == Map::GRP_RECT[c][d].PLATE_TYPE)
				{
					Map::GRP_RECT[a][b].PLATE_H += 0.01;
					if (Map::GRP_RECT[a][b].PLATE_H > Map::GRP_RECT[c][d].PLATE_H)
					{
						Map::GRP_RECT[a][b].PLATE_H -= 0.01;
						Map::GRP_RECT[c][d].PLATE_H += 0.01;
					}
					else if (Map::GRP_RECT[a][b].PLATE_H < Map::GRP_RECT[c][d].PLATE_H)
					{
						Map::GRP_RECT[a][b].PLATE_H += 0.01;
						Map::GRP_RECT[c][d].PLATE_H -= 0.01;
					}
				}
			}

			Map::GRP_RECT[a][b].PLATE_H -= 0.03;
		}
	}
	for (a = 0; a < Map::MAP_W; a++)
	{
		for (b = 0; b < Map::MAP_H; b++)
		{

			switch (MMD_)
			{
				case 0:
				{
					Map::GRP_RECT[a][b].SET_RGB(m_util->HSV2RGB((Map::GRP_RECT[a][b].PLATE_TYPE - 1.0) / (m_data.MAX_PLATE - 1.0) * 400.0 , 1.00, (Map::GRP_RECT[a][b].PLATE_H - MMD_H.MIN) / (MMD_H.MAX - MMD_H.MIN))); //((Map::GRP_RECT[a][b].PLATE_H - MMD_H.MIN) / (MMD_H.MAX - MMD_H.MIN) * 240), 10));

					break;
				}
				case 1:
				{
					Map::GRP_RECT[a][b].SET_RGB(m_util->HSV2RGB((Map::GRP_RECT[a][b].PLATE_TYPE - 1.0) / (m_data.MAX_PLATE - 1.0) * 400.0, 1.00, (Map::GRP_RECT[a][b].PLATE_P - MMD_P.MIN) / (MMD_P.MAX - MMD_P.MIN)));
					break;
				}
				case 2:
				{
					Map::GRP_RECT[a][b].SET_RGB(((Map::GRP_RECT[a][b].GEO_H - MMD_GH.MIN) / (MMD_GH.MAX - MMD_GH.MIN)) * 255.0, (1 - (Map::GRP_RECT[a][b].GEO_H - MMD_GH.MIN) / (MMD_GH.MAX - MMD_GH.MIN)) * 255.0, 0);
					break;
				}
				default:
					Map::GRP_RECT[a][b].SET_RGB(m_util->HSV2RGB((Map::GRP_RECT[a][b].PLATE_TYPE - 1.0) / (m_data.MAX_PLATE - 1.0) * 400.0, 1.00, 1.00));
					break;
			}

			av = true;
			for (w = 0; w < 8; w++)
			{
				c = (a + W[w][0] + Map::MAP_W) % Map::MAP_W;
				d = b + W[w][1];
				f = 1.0;
				if (w % 2 > 0)
				{
					f /= sqrt(2);
				}

				if (c >= 0 && d >= 0 && c < Map::MAP_W && d < Map::MAP_H)
				{
					if (Map::GRP_RECT[a][b].PLATE_TYPE > 0 )
					{
						if (Map::GRP_RECT[c][d].PLATE_TYPE == 0)
						{
							//OTHER = EMPTY
							if (Map::GRP_RECT[a][b].PLATE_H > 1.0&& av&& rand() % (8 - w) == 0)
							{
								if (Map::GRP_RECT[a][b].PLATE_H > 40000)
								{
									OutputDebugStringA("A");
								}
								Map::GRP_RECT[c][d].PLATE_TYPE = Map::GRP_RECT[a][b].PLATE_TYPE;
								e = (Map::GRP_RECT[a][b].PLATE_H) / 2.0* PLT_MVE;
								e = 0.5 * f * atan(Map::GRP_RECT[a][b].PLATE_MOVE[w] + 1) / M_PI_4;


								Map::GRP_RECT[a][b].PLATE_MOVE[w] *= 0.5;

								//Map::GRP_RECT[a][b].PLATE_P *= 1 - (e / Map::GRP_RECT[a][b].PLATE_H);
								Map::GRP_RECT[a][b].PLATE_H -= e;
								//Map::GRP_RECT[c][d].PLATE_P *= 1 - (e / Map::GRP_RECT[c][d].PLATE_H);
								Map::GRP_RECT[c][d].PLATE_H += e;
								av = !av;
							} 

						}
						else if (Map::GRP_RECT[a][b].PLATE_TYPE == Map::GRP_RECT[c][d].PLATE_TYPE)
						{
							//OTHER=ME
							if (Map::GRP_RECT[a][b].PLATE_H * (1 + Map::GRP_RECT[a][b].PLATE_MOVE[w]) > Map::GRP_RECT[c][d].PLATE_H * (1 + Map::GRP_RECT[c][d].PLATE_MOVE[(w + 4) % 8])  && av&& rand() % (8 - w) == 0)
							{
								e = (Map::GRP_RECT[a][b].PLATE_H) /2.0 * PLT_MVE;
								e *= 1.0 * atan((Map::GRP_RECT[a][b].PLATE_H * (1 + Map::GRP_RECT[a][b].PLATE_MOVE[w])) - (Map::GRP_RECT[c][d].PLATE_H * (1 + Map::GRP_RECT[c][d].PLATE_MOVE[(w + 4) % 8]))) / M_PI;

								Map::GRP_RECT[a][b].PLATE_MOVE[w] *= 0.5;
								Map::GRP_RECT[c][d].PLATE_MOVE[w] += Map::GRP_RECT[a][b].PLATE_MOVE[w];
								Map::GRP_RECT[c][d].PLATE_MOVE[(w + 4) % 8] *= 0.5;
								Map::GRP_RECT[a][b].PLATE_MOVE[(w + 4) % 8] += Map::GRP_RECT[c][d].PLATE_MOVE[(w + 4) % 8];

								Map::GRP_RECT[a][b].PLATE_P *= 1 - (e / Map::GRP_RECT[a][b].PLATE_H);
								Map::GRP_RECT[a][b].PLATE_H -= e;
								Map::GRP_RECT[c][d].PLATE_P *= 1 + (e / Map::GRP_RECT[c][d].PLATE_H);
								Map::GRP_RECT[c][d].PLATE_H += e;

								av = !av;
							}

						}
						else
						{
							//OTHER ELSE
							if (Map::GRP_RECT[a][b].PLATE_H > 1.0 && Map::GRP_RECT[a][b].PLATE_P > 1.0 && Map::GRP_RECT[c][d].PLATE_H < 0.1)
							{
								Map::GRP_RECT[c][d].PLATE_TYPE = Map::GRP_RECT[a][b].PLATE_TYPE;
								e = (Map::GRP_RECT[a][b].PLATE_H) / 2.0 * PLT_MVE;
								e = 0.5 * f * atan(Map::GRP_RECT[a][b].PLATE_MOVE[w] + 1) / M_PI_4;
								//Map::GRP_RECT[a][b].PLATE_P *= 1 - (e / Map::GRP_RECT[a][b].PLATE_H);
								Map::GRP_RECT[a][b].PLATE_H -= e;
								//Map::GRP_RECT[c][d].PLATE_P *= 1 - (e / Map::GRP_RECT[c][d].PLATE_H);
								Map::GRP_RECT[c][d].PLATE_H += e;
								av = !av;

								if (Map::GRP_RECT[a][b].PLATE_H < 0)
								{
									OutputDebugStringA("C\n");
								}
							}

							if (Map::GRP_RECT[a][b].PLATE_MOVE[w] * Map::GRP_RECT[a][b].PLATE_P > Map::GRP_RECT[c][d].PLATE_MOVE[(w + 4) % 4] * Map::GRP_RECT[c][d].PLATE_P)
							{
								e = Map::GRP_RECT[a][b].PLATE_MOVE[w] - Map::GRP_RECT[c][d].PLATE_MOVE[(w + 4) % 4];
								e *= 0.1 * Map::GRP_RECT[a][b].PLATE_P / Map::GRP_RECT[c][d].PLATE_P;

								Map::GRP_RECT[a][b].PLATE_MOVE[w] *= 0.5;
								Map::GRP_RECT[c][d].PLATE_MOVE[w] += Map::GRP_RECT[a][b].PLATE_MOVE[w];
								Map::GRP_RECT[c][d].PLATE_MOVE[(w + 4) % 8] *= 0.5;
								Map::GRP_RECT[a][b].PLATE_MOVE[(w + 4) % 8] += Map::GRP_RECT[c][d].PLATE_MOVE[(w + 4) % 8];

								Map::GRP_RECT[c][d].PLATE_P += e;
							}

						}
					}
					else
					{

					}

				}
			}
		}
	}
	return;
}


bool Map::RECT_EQUAL(Map_Rect a, Map_Rect b)
{
	if (a.R == b.R && a.G == b.G && a.B == b.B)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Map::GET_RECT(int a, int b, int c)
{
	switch (c)
	{
	case 0:
		return Map::GRP_RECT[a][b].R;
	case 1:
		return Map::GRP_RECT[a][b].G;
	case 2:
		return Map::GRP_RECT[a][b].B;
	default:
		return Map::GRP_RECT[a][b].R;
	}
	
}

bool Map::CHECK_RECT(int a, int b)
{
	return Map::GRP_RECT[a][b].A;
	return false;
}