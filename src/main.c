#include "libft.h"
#include "MLX42.h"
#include <stdio.h>

int	main()
{
	char *str = ft_strdup("lol\n");

	ft_printf("hey%s\n", str);
	// mlx_t	*lol1;
	mlx_t	*lol;
	// mlx_texture_t	*hotdog;
	// mlx_texture_t	*hotdog2;
	// mlx_image_t		*elep;
	// mlx_image_t		*elep2;
	xpm_t	*test;

	lol = mlx_init(1000, 1000, "Heeeey", true);
	test = mlx_load_xpm42("img.xpm42");
	if (test == NULL)
	{
		printf("lol\n");
		printf("%s\n", mlx_strerror(mlx_errno));
		return (1);
	}
	mlx_image_t	*elep = mlx_texture_to_image(lol, &test->texture);
	(void)elep;
	
	// lol1 = mlx_init(1000, 1000, "Hiiiii", true);
	// mlx_set_window_pos(lol1, 1000, 1000);
	// hotdog = mlx_load_png("elep.png");
	// hotdog2 = mlx_load_png("hotdog.png");
	// elep = mlx_texture_to_image(lol, hotdog2);
	// elep2 = mlx_texture_to_image(lol1, hotdog2);
	mlx_image_to_window(lol, elep, 0, 0);
	// mlx_image_to_window(lol1, elep2, 0, 0);
	
	// mlx_set_icon(lol, hotdog);
	mlx_loop(lol);
	// mlx_loop(lol1);
}
