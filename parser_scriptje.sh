#! /bin/bash

./cub3d mappies/parser_test/empty.cub
echo "-------------------"
./cub3d mappies/parser_test/wrong_extension.cup
echo "-------------------"
./cub3d mappies/parser_test/not_enough_textures.cub
echo "-------------------"
./cub3d mappies/parser_test/invalid_texture_path.cub
echo "-------------------"
./cub3d mappies/parser_test/invalid_colour.cub
echo "-------------------"
# ./cub3d mappies/parser_test/double_EA.cub /#segfault :(
echo "-------------------"
./cub3d mappies/parser_test/spaces_in_map.cub
echo "-------------------"
./cub3d mappies/parser_test/spaces_edge.cub
echo "-------------------"
./cub3d mappies/parser_test/no_player.cub
echo "-------------------"
./cub3d mappies/parser_test/garbage.cub
