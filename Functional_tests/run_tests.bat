@echo off
cd /d "%~dp0"
del out*.txt 2>nul
echo. > results.txt

echo 01. Normal path 4x7 >> results.txt
.\shortest_path.exe maze_01.txt coords_01.txt out01.txt >> results.txt 2>&1
type out01.txt >> results.txt 2>nul

echo. >> results.txt

echo 02. Straight path horizontal >> results.txt
.\shortest_path.exe maze_02.txt coords_02.txt out02.txt >> results.txt 2>&1
type out02.txt >> results.txt 2>nul

echo. >> results.txt

echo 03. Straight path vertical >> results.txt
.\shortest_path.exe maze_03.txt coords_03.txt out03.txt >> results.txt 2>&1
type out03.txt >> results.txt 2>nul

echo. >> results.txt

echo 04. Path around inner wall >> results.txt
.\shortest_path.exe maze_04.txt coords_04.txt out04.txt >> results.txt 2>&1
type out04.txt >> results.txt 2>nul

echo. >> results.txt

echo 05. 2x2 maze path exists >> results.txt
.\shortest_path.exe maze_05.txt coords_05.txt out05.txt >> results.txt 2>&1
type out05.txt >> results.txt 2>nul

echo. >> results.txt

echo 06. Two shortest paths >> results.txt
.\shortest_path.exe maze_06.txt coords_06.txt out06.txt >> results.txt 2>&1
type out06.txt >> results.txt 2>nul

echo. >> results.txt

echo 07. Long path 5x5 >> results.txt
.\shortest_path.exe maze_07.txt coords_07.txt out07.txt >> results.txt 2>&1
type out07.txt >> results.txt 2>nul

echo. >> results.txt

echo 08. Narrow corridor >> results.txt
.\shortest_path.exe maze_08.txt coords_08.txt out08.txt >> results.txt 2>&1
type out08.txt >> results.txt 2>nul

echo. >> results.txt

echo 09. Large maze 5x10 >> results.txt
.\shortest_path.exe maze_09.txt coords_09.txt out09.txt >> results.txt 2>&1
type out09.txt >> results.txt 2>nul

echo. >> results.txt

echo 10. Path length 1 step >> results.txt
.\shortest_path.exe maze_10.txt coords_10.txt out10.txt >> results.txt 2>&1
type out10.txt >> results.txt 2>nul

echo. >> results.txt

echo 11. No path - wall divides maze >> results.txt
.\shortest_path.exe maze_11.txt coords_11.txt out11.txt >> results.txt 2>&1
type out11.txt >> results.txt 2>nul

echo. >> results.txt

echo 12. No path - start isolated >> results.txt
.\shortest_path.exe maze_12.txt coords_12.txt out12.txt >> results.txt 2>&1
type out12.txt >> results.txt 2>nul

echo. >> results.txt

echo 13. No path - end isolated >> results.txt
.\shortest_path.exe maze_13.txt coords_13.txt out13.txt >> results.txt 2>&1
type out13.txt >> results.txt 2>nul

echo. >> results.txt

echo 14. No path - inner wall divides >> results.txt
.\shortest_path.exe maze_14.txt coords_14.txt out14.txt >> results.txt 2>&1
type out14.txt >> results.txt 2>nul

echo. >> results.txt

echo 15. No path - all passages isolated >> results.txt
.\shortest_path.exe maze_15.txt coords_15.txt out15.txt >> results.txt 2>&1
type out15.txt >> results.txt 2>nul

echo. >> results.txt

echo 16. Maze file does not exist >> results.txt
.\shortest_path.exe maze_nonexistent.txt coords_16.txt out16.txt >> results.txt 2>&1
type out16.txt >> results.txt 2>nul

echo. >> results.txt

echo 17. Maze file is empty >> results.txt
.\shortest_path.exe maze_17.txt coords_17.txt out17.txt >> results.txt 2>&1
type out17.txt >> results.txt 2>nul

echo. >> results.txt

echo 18. rows = 0 >> results.txt
.\shortest_path.exe maze_18.txt coords_18.txt out18.txt >> results.txt 2>&1
type out18.txt >> results.txt 2>nul

echo. >> results.txt

echo 19. rows = 256 >> results.txt
.\shortest_path.exe maze_19.txt coords_19.txt out19.txt >> results.txt 2>&1
type out19.txt >> results.txt 2>nul

echo. >> results.txt

echo 20. cols = 0 >> results.txt
.\shortest_path.exe maze_20.txt coords_20.txt out20.txt >> results.txt 2>&1
type out20.txt >> results.txt 2>nul

echo. >> results.txt

echo 21. cols = 256 >> results.txt
.\shortest_path.exe maze_21.txt coords_21.txt out21.txt >> results.txt 2>&1
type out21.txt >> results.txt 2>nul

echo. >> results.txt

echo 22. First line is letters not number >> results.txt
.\shortest_path.exe maze_22.txt coords_22.txt out22.txt >> results.txt 2>&1
type out22.txt >> results.txt 2>nul

echo. >> results.txt

echo 23. Second line is letters not number >> results.txt
.\shortest_path.exe maze_23.txt coords_23.txt out23.txt >> results.txt 2>&1
type out23.txt >> results.txt 2>nul

echo. >> results.txt

echo 24. Fewer rows than declared >> results.txt
.\shortest_path.exe maze_24.txt coords_24.txt out24.txt >> results.txt 2>&1
type out24.txt >> results.txt 2>nul

echo. >> results.txt

echo 25. More rows than declared >> results.txt
.\shortest_path.exe maze_25.txt coords_25.txt out25.txt >> results.txt 2>&1
type out25.txt >> results.txt 2>nul

echo. >> results.txt

echo 26. Row shorter than declared cols >> results.txt
.\shortest_path.exe maze_26.txt coords_26.txt out26.txt >> results.txt 2>&1
type out26.txt >> results.txt 2>nul

echo. >> results.txt

echo 27. Row longer than declared cols >> results.txt
.\shortest_path.exe maze_27.txt coords_27.txt out27.txt >> results.txt 2>&1
type out27.txt >> results.txt 2>nul

echo. >> results.txt

echo 28. Invalid character in maze >> results.txt
.\shortest_path.exe maze_28.txt coords_28.txt out28.txt >> results.txt 2>&1
type out28.txt >> results.txt 2>nul

echo. >> results.txt

echo 29. All walls - no passage >> results.txt
.\shortest_path.exe maze_29.txt coords_29.txt out29.txt >> results.txt 2>&1
type out29.txt >> results.txt 2>nul

echo. >> results.txt

echo 30. Maze with spaces between symbols >> results.txt
.\shortest_path.exe maze_30.txt coords_30.txt out30.txt >> results.txt 2>&1
type out30.txt >> results.txt 2>nul

echo. >> results.txt

echo 31. Coords file does not exist >> results.txt
.\shortest_path.exe maze_31.txt coords_nonexistent.txt out31.txt >> results.txt 2>&1
type out31.txt >> results.txt 2>nul

echo. >> results.txt

echo 32. Coords file is empty >> results.txt
.\shortest_path.exe maze_32.txt coords_32.txt out32.txt >> results.txt 2>&1
type out32.txt >> results.txt 2>nul

echo. >> results.txt

echo 33. Only one line of coords >> results.txt
.\shortest_path.exe maze_33.txt coords_33.txt out33.txt >> results.txt 2>&1
type out33.txt >> results.txt 2>nul

echo. >> results.txt

echo 34. Three lines of coords >> results.txt
.\shortest_path.exe maze_34.txt coords_34.txt out34.txt >> results.txt 2>&1
type out34.txt >> results.txt 2>nul

echo. >> results.txt

echo 35. Three numbers in first coords line >> results.txt
.\shortest_path.exe maze_35.txt coords_35.txt out35.txt >> results.txt 2>&1
type out35.txt >> results.txt 2>nul

echo. >> results.txt

echo 36. Three numbers in second coords line >> results.txt
.\shortest_path.exe maze_36.txt coords_36.txt out36.txt >> results.txt 2>&1
type out36.txt >> results.txt 2>nul

echo. >> results.txt

echo 37. Coords are letters >> results.txt
.\shortest_path.exe maze_37.txt coords_37.txt out37.txt >> results.txt 2>&1
type out37.txt >> results.txt 2>nul

echo. >> results.txt

echo 38. Negative start row >> results.txt
.\shortest_path.exe maze_38.txt coords_38.txt out38.txt >> results.txt 2>&1
type out38.txt >> results.txt 2>nul

echo. >> results.txt

echo 39. Negative start col >> results.txt
.\shortest_path.exe maze_39.txt coords_39.txt out39.txt >> results.txt 2>&1
type out39.txt >> results.txt 2>nul

echo. >> results.txt

echo 40. Start row out of bounds >> results.txt
.\shortest_path.exe maze_40.txt coords_40.txt out40.txt >> results.txt 2>&1
type out40.txt >> results.txt 2>nul

echo. >> results.txt

echo 41. Start col out of bounds >> results.txt
.\shortest_path.exe maze_41.txt coords_41.txt out41.txt >> results.txt 2>&1
type out41.txt >> results.txt 2>nul

echo. >> results.txt

echo 42. End row out of bounds >> results.txt
.\shortest_path.exe maze_42.txt coords_42.txt out42.txt >> results.txt 2>&1
type out42.txt >> results.txt 2>nul

echo. >> results.txt

echo 43. End col out of bounds >> results.txt
.\shortest_path.exe maze_43.txt coords_43.txt out43.txt >> results.txt 2>&1
type out43.txt >> results.txt 2>nul

echo. >> results.txt

echo 44. Start point is wall >> results.txt
.\shortest_path.exe maze_44.txt coords_44.txt out44.txt >> results.txt 2>&1
type out44.txt >> results.txt 2>nul

echo. >> results.txt

echo 45. End point is wall >> results.txt
.\shortest_path.exe maze_45.txt coords_45.txt out45.txt >> results.txt 2>&1
type out45.txt >> results.txt 2>nul

echo. >> results.txt

echo 46. Both points are walls >> results.txt
.\shortest_path.exe maze_46.txt coords_46.txt out46.txt >> results.txt 2>&1
type out46.txt >> results.txt 2>nul

echo. >> results.txt

echo 47. Start and end points are the same >> results.txt
.\shortest_path.exe maze_47.txt coords_47.txt out47.txt >> results.txt 2>&1
type out47.txt >> results.txt 2>nul

echo. >> results.txt

echo 48. Float coordinates >> results.txt
.\shortest_path.exe maze_48.txt coords_48.txt out48.txt >> results.txt 2>&1
type out48.txt >> results.txt 2>nul

echo. >> results.txt

echo 49. Extra spaces in coords >> results.txt
.\shortest_path.exe maze_49.txt coords_49.txt out49.txt >> results.txt 2>&1
type out49.txt >> results.txt 2>nul

echo. >> results.txt

echo 50. No arguments >> results.txt
.\shortest_path.exe >> results.txt 2>&1

echo. >> results.txt

echo 51. One argument >> results.txt
.\shortest_path.exe maze_01.txt >> results.txt 2>&1

echo. >> results.txt

echo 52. Two arguments >> results.txt
.\shortest_path.exe maze_01.txt coords_01.txt >> results.txt 2>&1

echo. >> results.txt

echo 53. Five arguments >> results.txt
.\shortest_path.exe maze_01.txt coords_01.txt out53.txt extra1.txt extra2.txt >> results.txt 2>&1

echo. >> results.txt

echo 54. Invalid output file path >> results.txt
.\shortest_path.exe maze_54.txt coords_54.txt C:\nonexistent_folder\out54.txt >> results.txt 2>&1

echo. >> results.txt

echo 55. 1x2 maze path exists >> results.txt
.\shortest_path.exe maze_55.txt coords_55.txt out55.txt >> results.txt 2>&1
type out55.txt >> results.txt 2>nul

echo. >> results.txt

echo 56. 2x1 maze path exists >> results.txt
.\shortest_path.exe maze_56.txt coords_56.txt out56.txt >> results.txt 2>&1
type out56.txt >> results.txt 2>nul

echo. >> results.txt

echo 57. Start top-left end bottom-right 5x5 >> results.txt
.\shortest_path.exe maze_57.txt coords_57.txt out57.txt >> results.txt 2>&1
type out57.txt >> results.txt 2>nul

echo. >> results.txt

echo 58. All passages 5x5 diagonal >> results.txt
.\shortest_path.exe maze_58.txt coords_58.txt out58.txt >> results.txt 2>&1
type out58.txt >> results.txt 2>nul

echo. >> results.txt

echo 59. Snake maze >> results.txt
.\shortest_path.exe maze_59.txt coords_59.txt out59.txt >> results.txt 2>&1
type out59.txt >> results.txt 2>nul

echo. >> results.txt

echo 60. Path only right >> results.txt
.\shortest_path.exe maze_60.txt coords_60.txt out60.txt >> results.txt 2>&1
type out60.txt >> results.txt 2>nul

echo. >> results.txt

echo 61. Path only down >> results.txt
.\shortest_path.exe maze_61.txt coords_61.txt out61.txt >> results.txt 2>&1
type out61.txt >> results.txt 2>nul

echo. >> results.txt

echo 62. Path right then down >> results.txt
.\shortest_path.exe maze_62.txt coords_62.txt out62.txt >> results.txt 2>&1
type out62.txt >> results.txt 2>nul

echo. >> results.txt

echo 63. Path down then right >> results.txt
.\shortest_path.exe maze_63.txt coords_63.txt out63.txt >> results.txt 2>&1
type out63.txt >> results.txt 2>nul

echo. >> results.txt

echo 64. Path with turns >> results.txt
.\shortest_path.exe maze_64.txt coords_64.txt out64.txt >> results.txt 2>&1
type out64.txt >> results.txt 2>nul

echo. >> results.txt

echo 65. Start left edge end right edge >> results.txt
.\shortest_path.exe maze_65.txt coords_65.txt out65.txt >> results.txt 2>&1
type out65.txt >> results.txt 2>nul

echo. >> results.txt

echo 66. Maze with dead ends >> results.txt
.\shortest_path.exe maze_66.txt coords_66.txt out66.txt >> results.txt 2>&1
type out66.txt >> results.txt 2>nul

echo. >> results.txt

echo 67. 1x1 maze same start and end - error >> results.txt
.\shortest_path.exe maze_67.txt coords_67.txt out67.txt >> results.txt 2>&1
type out67.txt >> results.txt 2>nul

echo. >> results.txt

echo 68. Path length 1 step down >> results.txt
.\shortest_path.exe maze_68.txt coords_68.txt out68.txt >> results.txt 2>&1
type out68.txt >> results.txt 2>nul

echo. >> results.txt

echo 69. BFS shortest path around wall >> results.txt
.\shortest_path.exe maze_69.txt coords_69.txt out69.txt >> results.txt 2>&1
type out69.txt >> results.txt 2>nul

echo. >> results.txt

echo 70. BFS avoids dead ends >> results.txt
.\shortest_path.exe maze_70.txt coords_70.txt out70.txt >> results.txt 2>&1
type out70.txt >> results.txt 2>nul

echo. >> results.txt

echo 71. First cell of path equals start >> results.txt
.\shortest_path.exe maze_71.txt coords_71.txt out71.txt >> results.txt 2>&1
type out71.txt >> results.txt 2>nul

echo. >> results.txt

echo 72. Last cell of path equals end >> results.txt
.\shortest_path.exe maze_72.txt coords_72.txt out72.txt >> results.txt 2>&1
type out72.txt >> results.txt 2>nul

echo. >> results.txt

echo 73. Path does not go through walls >> results.txt
.\shortest_path.exe maze_73.txt coords_73.txt out73.txt >> results.txt 2>&1
type out73.txt >> results.txt 2>nul

echo. >> results.txt

echo 74. BFS guarantees shortest path >> results.txt
.\shortest_path.exe maze_74.txt coords_74.txt out74.txt >> results.txt 2>&1
type out74.txt >> results.txt 2>nul

echo. >> results.txt

echo 75. Maze with multiple dead ends finds way >> results.txt
.\shortest_path.exe maze_75.txt coords_75.txt out75.txt >> results.txt 2>&1
type out75.txt >> results.txt 2>nul

echo. >> results.txt
echo All tests done. See results.txt