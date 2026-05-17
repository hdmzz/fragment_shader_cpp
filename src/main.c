#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	size_t	index = 0;
	char	buffer[256];
	while (index < 60) {
		snprintf(buffer, sizeof(buffer), "output-0%02d.ppm", index); 
		const char	*output_path 	= buffer;
		FILE		*file		= fopen(output_path, "wb");
		size_t		width		= 16 * 60;
		size_t		heigth		= 9 * 60;

		fprintf(file, "P6\n");
		fprintf(file, "%d %d\n", width, heigth);
		fprintf(file, "255\n");

		for (size_t y = 0; y < heigth; y++) {
			for (size_t i = 0; i < width; i++) {
				if ((i / 60) % 2) {
					fputc(0x00, file);
					fputc(0xFF, file);
					fputc(0x00, file);
				} else {
					fputc(0x00, file);
					fputc(0x00, file);
					fputc(0x00, file);
				}
			}
		}

		fclose(file);
		printf("Generated %s\n", output_path);
		index++;
	}
	return 0;
}	

