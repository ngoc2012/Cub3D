double	angle_convert(double a)
{
	while (a > 180.0 || a <= -180.0)
	{
		if (a > 180.0)
			a -= 360.0;
		if (a <= -180.0)
			a += 360.0;
	}
	return (a);
}
