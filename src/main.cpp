#include <stdio.h>
#include <ostream>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cmath>

struct vec4 {
	float	x, y, z, w;
	vec4(float x = 0, float y = 0, float z = 0, float w = 0): x(x), y(y), z(z), w(w) {}
};

struct vec2 {
	float	x, y;
	vec2(float x = 0, float y = 0): x(x), y(y) {}
	vec2	yx() const { return vec2(y, x); }
	vec4	xyyx() const { return vec4(x, y, y, x); }
};

vec2	operator *(const vec2 &a, float s) { return vec2(a.x * s, a.y * s); }
vec2	operator -(const vec2 &a, const vec2 &b) { return vec2(a.x - b.x, a.y - b.y); }
vec2	operator /(const vec2 &a, float s) { return vec2(a.x / s, a.y / s); }
vec2	operator +(const vec2 &a, const vec2 &b) { return vec2(a.x + b.x, a.y + b.y); }


float	dot(const vec2 &a, const vec2 &b) { return a.x * b.x + a.y * b.y; }

vec4	sin(const vec4 &a) { return vec4(sinf(a.x), sinf(a.y),  sinf(a.z),  sinf(a.w)); }

int	main(void)
{
	size_t	i = 0;
	char	buffer[256];

	while (i < 60) {
		snprintf(buffer, sizeof(buffer), "output-%02d.ppm", i); 
		const char	*output_path 	= buffer;
		FILE		*file		= fopen(output_path, "wb");
		size_t		width		= 16 * 60;
		size_t		heigth		= 9 * 60;

		fprintf(file, "P6\n");
		fprintf(file, "%d %d\n", width, heigth);
		fprintf(file, "255\n");

		vec2	r = {(float)width, (float)heigth};
		for (size_t x = 0; x < heigth; x++) {
			for (size_t y = 0; y < width; y++) {
				vec4	o;
				vec2	FC = {(float)x, (float)y};
				vec2	p = (FC * 2. - r) / r.y;
				vec2	i;
				vec2	l;
				vec2	v = p * (l += 4. - 4. * abs(.7 - dot(p, p)));

				for (; i.y++ < 8. ; o += (sin(v.xyyx()) + 1.) * abs(v.x - v.y)) { 
					v += cos(v.yx() * i.y + i + t) / i.y + .7;
				}

				o = tanh(5. * exp(l.x - 4. - p.y * vec4(-1, 1, 2, 0)) / o);

				fputc(o.x*255, file);
				fputc(o.y*255, file);
				fputc(o.z*255, file);
			}
		}

		fclose(file);
		std::cout << "Generated " << output_path << std::endl;
		i++;
	}
	return 0;
}	

