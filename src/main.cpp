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
vec2	operator *(const vec2 &a, const vec2 &b) { return vec2(a.x * b.x, a.y * b.y); }
vec4	operator *(const vec4 &a, float s) { return vec4(a.x * s, a.y * s, a.z * s, a.w * s); }
vec4	operator *(float s, const vec4 &a) { return a * s; }

vec2	operator -(const vec2 &a, const vec2 &b) { return vec2(a.x - b.x, a.y - b.y); }
vec4	operator -(float s, const vec4 &a) { return vec4(a.x - s, a.y - s,  a.z - s, a.w - s ); }

vec2	operator /(const vec2 &a, float s) { return vec2(a.x / s, a.y / s); }
vec4	operator /(const vec4 &a, const vec4 &b) { return vec4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w ); }

vec2	operator +(const vec2 &a, const vec2 &b) { return vec2(a.x + b.x, a.y + b.y); }
vec2	operator +(const vec2 &a, float s) { return vec2(a.x + s, a.y + s); }
vec4	operator +(const vec4 &a, float s) { return vec4(a.x + s, a.y + s, a.z + s, a.w + s); }
vec4	operator +(const vec4 &a, const vec4 &b) { return vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }

vec2	&operator +=(vec2 &a, float s) { a = a + s; return a; }
vec2	&operator +=(vec2 &a, const vec2 &b) { a = a + b; return a; }
vec4	&operator +=(vec4 &a, const vec4 &b) { a = a + b; return a; }

float	dot(const vec2 &a, const vec2 &b) { return a.x * b.x + a.y * b.y; }

vec2	cos(const vec2 &a) { return vec2(cosf(a.x), cosf(a.y)); }

vec4	sin(const vec4 &a) { return vec4(sinf(a.x), sinf(a.y),  sinf(a.z),  sinf(a.w)); }
vec4	tanh(const vec4 &a) { return vec4(tanhf(a.x), tanhf(a.y), tanhf(a.z), tanhf(a.w)); }
vec4	exp(const vec4 &a) { return vec4(expf(a.x), expf(a.y), expf(a.z), expf(a.w)); }

int	main(void)
{
	int	LAP = 240;
	int	i = 0;
	char	buffer[256];

	while (i < LAP) {
		snprintf(buffer, sizeof(buffer), "output-%03d.ppm", i); 
		const char	*output_path 	= buffer;
		FILE		*file		= fopen(output_path, "wb");
		int		width		= 16 * 60;
		int		heigth		= 9 * 60;

		fprintf(file, "P6\n");
		fprintf(file, "%d %d\n", width, heigth);
		fprintf(file, "255\n");

		vec2	r = {(float)width, (float)heigth};
		float	t = ((float)i / LAP) * 2 * M_PI;
		for (int y = 0; y < heigth; y++) {
			for (int x = 0; x < width; x++) {
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

