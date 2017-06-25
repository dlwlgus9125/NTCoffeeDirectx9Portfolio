#include "stdafx.h"
#include "cObjectDB.h"


void cObjectDB::Setup()
{
	//							대분류					중분류					소분류									폴더 경로											파일명											u값						v값
	// Human
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DUSKWOOD, E_S_OBJECTID_H_DW_BARN, "obj/Construct/Human/Duskwood/Barn", "duskwood_barn.obj", 0, 0));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DUSKWOOD, E_S_OBJECTID_H_DW_BLACKSMITH, "obj/Construct/Human/Duskwood/Blacksmith", "duskwood_blacksmith.obj", (float)1 / 8, 0));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DUSKWOOD, E_S_OBJECTID_H_DW_CHAPEL, "obj/Construct/Human/Duskwood/Chapel", "duskwoodchapel.obj", (float)2 / 8, 0));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DUSKWOOD, E_S_OBJECTID_H_DW_FARM, "obj/Construct/Human/Duskwood/Farm", "duskwood_human_farm.obj", (float)3 / 8, 0));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DUSKWOOD, E_S_OBJECTID_H_DW_INN, "obj/Construct/Human/Duskwood/Inn", "duskwood_inn.obj", (float)4 / 8, 0));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DUSKWOOD, E_S_OBJECTID_H_DW_LUMBERMILL, "obj/Construct/Human/Duskwood/Lumbermill", "duskwood_lumbermill.obj", (float)5 / 8, 0));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DUSKWOOD, E_S_OBJECTID_H_DW_MAGETOWER, "obj/Construct/Human/Duskwood/MageTower", "duskwood_magetower.obj", (float)6 / 8, 0));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DUSKWOOD, E_S_OBJECTID_H_DW_STABLE, "obj/Construct/Human/Duskwood/Stable", "duskwood_stable.obj", (float)7 / 8, 0));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DUSKWOOD, E_S_OBJECTID_H_DW_TWOSTORYHOUSE, "obj/Construct/Human/Duskwood/Two-story", "duskwood_humantwostory.obj", 0, (float)1 / 16));

	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_ALCHEMYHUB, "obj/Construct/Human/Draenor/AlchemyHub", "6hu_garrison_alchemy_hub.obj", (float)1 / 8, (float)1 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_ALCHEMYRANK, "obj/Construct/Human/Draenor/AlchemyRank", "6hu_garrison_alchemy_rank1.obj", (float)2 / 8, (float)1 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_ARMORY, "obj/Construct/Human/Draenor/Armory", "6hu_garrison_armory_v1.obj", (float)3 / 8, (float)1 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_BARN, "obj/Construct/Human/Draenor/Barn", "6hu_garrison_barn_v1.obj", (float)4 / 8, (float)1 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_BARRACKS, "obj/Construct/Human/Draenor/Barracks", "6hu_garrison_barracks_v2.obj", (float)5 / 8, (float)1 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_BELLTOWER, "obj/Construct/Human/Draenor/BellTower", "6hu_garrison_belltower.obj", (float)6 / 8, (float)1 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_BLACKSMITH, "obj/Construct/Human/Draenor/Blacksmith", "6hu_garrison_blacksmithing_hub.obj", (float)7 / 8, (float)1 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_FARM, "obj/Construct/Human/Draenor/Farm", "6hu_garrison_farm_v1.obj", 0, (float)2 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_FOOTBRIDGE, "obj/Construct/Human/Draenor/FootBridge", "6hu_garrison_footbridge_v1.obj", (float)1 / 8, (float)2 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_GARDENHOUSE, "obj/Construct/Human/Draenor/GardenHouse", "6hu_garrison_gardenhouse_v1.obj", (float)2 / 8, (float)2 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_GATE1, "obj/Construct/Human/Draenor/Gate1", "6hu_garrison_gate_v2.obj", (float)3 / 8, (float)2 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_GATE2, "obj/Construct/Human/Draenor/Gate2", "6hu_garrison_gate_v3.obj", (float)4 / 8, (float)2 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_INFIRMARY, "obj/Construct/Human/Draenor/Infirmary", "6hu_garrison_infirmary_v2.obj", (float)5 / 8, (float)2 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_INN, "obj/Construct/Human/Draenor/Inn", "6hu_garrison_inn_v3.obj", (float)6 / 8, (float)2 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_SMALLSTAIR1, "obj/Construct/Human/Draenor/SmallStair1", "6hu_garrison_stair_v1.obj", (float)7 / 8, (float)2 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_SMALLSTAIR2, "obj/Construct/Human/Draenor/SmallStair2", "6hu_garrison_stair_v2.obj", 0, (float)3 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_SMALLSTAIR3, "obj/Construct/Human/Draenor/SmallStair3", "6hu_garrison_stair_v3.obj", (float)1 / 8, (float)3 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_LARGESTAIR1, "obj/Construct/Human/Draenor/LargeStair1", "6hu_garrison_stair02_v1.obj", (float)2 / 8, (float)3 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_LARGESTAIR2, "obj/Construct/Human/Draenor/LargeStair2", "6hu_garrison_stair02_v2.obj", (float)3 / 8, (float)3 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_LARGESTAIR3, "obj/Construct/Human/Draenor/LargeStair3", "6hu_garrison_stair02_v3.obj", (float)4 / 8, (float)3 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_MAGETOWER, "obj/Construct/Human/Draenor/MageTower", "6hu_garrison_magictower_v3.obj", (float)5 / 8, (float)3 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_MENAGERIE, "obj/Construct/Human/Draenor/Menagerie", "6hu_garrison_menagerie.obj", (float)6 / 8, (float)3 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_RETAININGWALL, "obj/Construct/Human/Draenor/RetainingWall", "6hu_garrison_retaining_wall.obj", (float)7 / 8, (float)3 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_RETAININGWALL_PILLAR, "obj/Construct/Human/Draenor/RetainingWall_Pillar", "6hu_garrison_retainingwall_pillar.obj", 0, (float)4 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_TOWER1, "obj/Construct/Human/Draenor/Tower1", "6hu_garrison_tower_v2.obj", (float)1 / 8, (float)4 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_TOWER2, "obj/Construct/Human/Draenor/Tower2", "6hu_garrison_tower_v3.obj", (float)2 / 8, (float)4 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_HUMAN, E_M_OBJECTID_H_DRAENOR, E_S_OBJECTID_H_DN_TRADINGPOST, "obj/Construct/Human/Draenor/Tradingpost", "6hu_garrison_tradingpost_v3.obj", (float)3 / 8, (float)4 / 16));

	// Orc
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_KALIMDOR, E_S_OBJECTID_O_KD_BARRACKS, "obj/Construct/Orc/Kalimdor/Barracks", "orcbarracks.obj", (float)4 / 8, (float)4 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_KALIMDOR, E_S_OBJECTID_O_KD_BLACKSMITH, "obj/Construct/Orc/Kalimdor/Blacksmith", "orcblacksmith.obj", (float)5 / 8, (float)4 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_KALIMDOR, E_S_OBJECTID_O_KD_GREATHALL, "obj/Construct/Orc/Kalimdor/GreatHall", "orcgreathall.obj", (float)6 / 8, (float)4 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_KALIMDOR, E_S_OBJECTID_O_KD_HUT, "obj/Construct/Orc/Kalimdor/Hut", "orchut.obj", (float)7 / 8, (float)4 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_KALIMDOR, E_S_OBJECTID_O_KD_INN, "obj/Construct/Orc/Kalimdor/Inn", "orcinn.obj", 0, (float)5 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_KALIMDOR, E_S_OBJECTID_O_KD_KENNEL, "obj/Construct/Orc/Kalimdor/Kennel", "orckennel.obj", (float)1 / 8, (float)5 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_KALIMDOR, E_S_OBJECTID_O_KD_MAGETOWER, "obj/Construct/Orc/Kalimdor/MageTower", "orcmagetower.obj", (float)2 / 8, (float)5 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_KALIMDOR, E_S_OBJECTID_O_KD_MEDIUM, "obj/Construct/Orc/Kalimdor/Medium", "orcmedium.obj", (float)3 / 8, (float)5 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_KALIMDOR, E_S_OBJECTID_O_KD_TOWER, "obj/Construct/Orc/Kalimdor/Tower", "orctower.obj", (float)4 / 8, (float)5 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_KALIMDOR, E_S_OBJECTID_O_KD_TWOSTORYHOUSE, "obj/Construct/Orc/Kalimdor/Two-story", "orctwostory.obj", (float)5 / 8, (float)5 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_KALIMDOR, E_S_OBJECTID_O_KD_ZEPPELINHOUSE, "obj/Construct/Orc/Kalimdor/Zeppelinhouse", "orczeppelinhouse.obj", (float)6 / 8, (float)5 / 16));

	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_NORTHREND, E_S_OBJECTID_O_NR_BEARPIT, "obj/Construct/Orc/Northrend/Bearpit", "nd_winterorc_bearpit.obj", (float)7 / 8, (float)5 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_NORTHREND, E_S_OBJECTID_O_NR_CAP, "obj/Construct/Orc/Northrend/Cap", "nd_winterorc_cap1.obj", 0, (float)6 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_NORTHREND, E_S_OBJECTID_O_NR_CRANE, "obj/Construct/Orc/Northrend/Crane", "nd_orcwinter_crane.obj", (float)1 / 8, (float)6 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_NORTHREND, E_S_OBJECTID_O_NR_FORGE, "obj/Construct/Orc/Northrend/Forge", "nd_winterorc_forge.obj", (float)2 / 8, (float)6 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_NORTHREND, E_S_OBJECTID_O_NR_GATE, "obj/Construct/Orc/Northrend/Gate", "nd_winterorc_gate.obj", (float)3 / 8, (float)6 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_NORTHREND, E_S_OBJECTID_O_NR_HORDEGUNSHIP, "obj/Construct/Orc/Northrend/Hordegunship", "nd_hordegunship.obj", (float)4 / 8, (float)6 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_NORTHREND, E_S_OBJECTID_O_NR_HOVEL, "obj/Construct/Orc/Northrend/Hovel", "nd_winterorc_hovel.obj", (float)5 / 8, (float)6 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_NORTHREND, E_S_OBJECTID_O_NR_SCAFFOLD, "obj/Construct/Orc/Northrend/Scaffold", "nd_winterorc_scaffoldng_01.obj", (float)6 / 8, (float)6 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_NORTHREND, E_S_OBJECTID_O_NR_SHIP, "obj/Construct/Orc/Northrend/Ship", "orc_ship_01.obj", (float)7 / 8, (float)6 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_NORTHREND, E_S_OBJECTID_O_NR_STABLE, "obj/Construct/Orc/Northrend/Stable", "nd_winterorc_stables.obj", 0, (float)7 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_NORTHREND, E_S_OBJECTID_O_NR_TOWER1, "obj/Construct/Orc/Northrend/Tower1", "nd_winterorc_tower.obj", (float)1 / 8, (float)7 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_NORTHREND, E_S_OBJECTID_O_NR_TOWER2, "obj/Construct/Orc/Northrend/Tower2", "nd_winterorc_tower_open.obj", (float)2 / 8, (float)7 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_NORTHREND, E_S_OBJECTID_O_NR_WALL1, "obj/Construct/Orc/Northrend/Wall", "nd_winterorc_wall.obj", (float)3 / 8, (float)7 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_ORC, E_M_OBJECTID_O_NORTHREND, E_S_OBJECTID_O_NR_WALL2, "obj/Construct/Orc/Northrend/Wall2", "nd_winterorc_wall2.obj", (float)4 / 8, (float)7 / 16));

	// Props
	Add(new ST_OBJECTDATA(E_L_OBJECTID_PROPS, E_M_OBJECTID_P_DUSKWOOD, E_S_OBJECTID_P_DW_TREE1, "obj/Props/Duskwood/C2_Tree", "duskwoodtreespookless02_[0]_Stand_14414.obj", 0, (float)8 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_PROPS, E_M_OBJECTID_P_DUSKWOOD, E_S_OBJECTID_P_DW_TREE2, "obj/Props/Duskwood/C4_Tree", "duskwoodtree05_[0]_Stand_2837.obj", (float)1 / 8, (float)8 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_PROPS, E_M_OBJECTID_P_DUSKWOOD, E_S_OBJECTID_P_DW_TREE3, "obj/Props/Duskwood/C5_Tree", "duskwoodtreestump01_[0]_Stand_1471.obj", (float)2 / 8, (float)8 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_PROPS, E_M_OBJECTID_P_DUSKWOOD, E_S_OBJECTID_P_DW_TREE4, "obj/Props/Duskwood/C6_Tree", "newduskwoodtreehuge_[0]_Stand_7061.obj", (float)3 / 8, (float)8 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_PROPS, E_M_OBJECTID_P_DUSKWOOD, E_S_OBJECTID_P_DW_ROCK1, "obj/Props/Duskwood/C7_Rock", "duskwoodboulder01_[0]_Stand_500.obj", (float)4 / 8, (float)8 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_PROPS, E_M_OBJECTID_P_DUSKWOOD, E_S_OBJECTID_P_DW_ROCK2, "obj/Props/Duskwood/C8_Rock", "duskwoodboulder02_[0]_Stand_47.obj", (float)5 / 8, (float)8 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_PROPS, E_M_OBJECTID_P_DUSKWOOD, E_S_OBJECTID_P_DW_ROCK3, "obj/Props/Duskwood/C9_Rock", "duskwoodboulder03_[0]_Stand_2985.obj", (float)6 / 8, (float)8 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_PROPS, E_M_OBJECTID_P_DUSKWOOD, E_S_OBJECTID_P_DW_BENCH, "obj/Props/Duskwood/C10_Bench", "duskwoodbench_[0]_Stand_203.obj", (float)7 / 8, (float)8 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_PROPS, E_M_OBJECTID_P_DUSKWOOD, E_S_OBJECTID_P_DW_TABLE, "obj/Props/Duskwood/C11_Table", "duskwoodtable01_[0]_Stand_2984.obj", 0, (float)9 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_PROPS, E_M_OBJECTID_P_DUSKWOOD, E_S_OBJECTID_P_DW_HAYWAGON, "obj/Props/Duskwood/C12_Haywagon", "duskwoodhaywagon_[0]_Stand_1156.obj", (float)1 / 8, (float)9 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_PROPS, E_M_OBJECTID_P_DUSKWOOD, E_S_OBJECTID_P_DW_BRICK, "obj/Props/Duskwood/C15_Brick", "duskwood_magetower_brick_[0]_Stand_1781.obj", (float)2 / 8, (float)9 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_PROPS, E_M_OBJECTID_P_NORTHREND, E_S_OBJECTID_P_NR_ROCK1, "obj/Props/Northrend/C16_Rock", "northrendbg2_rocks_02_[0]_Stand_3563.obj", (float)3 / 8, (float)9 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_PROPS, E_M_OBJECTID_P_NORTHREND, E_S_OBJECTID_P_NR_ROCK2, "obj/Props/Northrend/C17_Rock", "northrendbg2_rocks_04_[0]_Stand_3204.obj", (float)4 / 8, (float)9 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_PROPS, E_M_OBJECTID_P_NORTHREND, E_S_OBJECTID_P_NR_ROCK3, "obj/Props/Northrend/C18_Rock", "northrendbg2_rocks_06_[0]_Stand_4344.obj", (float)5 / 8, (float)9 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_PROPS, E_M_OBJECTID_P_NORTHREND, E_S_OBJECTID_P_NR_FENCE1, "obj/Props/Northrend/C19_Fence", "hu_fence05_northrend_[0]_Stand_3031.obj", (float)6 / 8, (float)9 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_PROPS, E_M_OBJECTID_P_NORTHREND, E_S_OBJECTID_P_NR_FENCE2, "obj/Props/Northrend/C20_Fence", "hu_fence06_northrend_[0]_Stand_188.obj", (float)7 / 8, (float)9 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_PROPS, E_M_OBJECTID_P_NORTHREND, E_S_OBJECTID_P_NR_FENCE3, "obj/Props/Northrend/C21_Fence", "hu_fencepost_northrend_[0]_Stand_2954.obj", 0, (float)10 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_PROPS, E_M_OBJECTID_P_ETC, E_S_OBJECTID_P_ETC_TREE1, "obj/Props/Etc/C24_Tree", "tirisfalgladetree01_[0]_Stand_1012.obj", (float)1 / 8, (float)10 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_PROPS, E_M_OBJECTID_P_ETC, E_S_OBJECTID_P_ETC_TREE2, "obj/Props/Etc/C25_Tree", "tirisfallgladecanopytree05_[0]_Stand_2748.obj", (float)2 / 8, (float)10 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_PROPS, E_M_OBJECTID_P_ETC, E_S_OBJECTID_P_ETC_TREE3, "obj/Props/Etc/C31_Tree", "wetlandtree01_[0]_Stand_2141.obj", (float)3 / 8, (float)10 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_PROPS, E_M_OBJECTID_P_ETC, E_S_OBJECTID_P_ETC_TREE4, "obj/Props/Etc/C33_Tree", "ironforgetree02_[0]_Stand_2469.obj", (float)4 / 8, (float)10 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_PROPS, E_M_OBJECTID_P_ETC, E_S_OBJECTID_P_ETC_TREE5, "obj/Props/Etc/C34_Tree", "ironforgetree03_[0]_Stand_94.obj", (float)5 / 8, (float)10 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_PROPS, E_M_OBJECTID_P_ETC, E_S_OBJECTID_P_ETC_TREE6, "obj/Props/Etc/C35_Tree", "ironforgetree04_[0]_Stand_1187.obj", (float)6 / 8, (float)10 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_PROPS, E_M_OBJECTID_P_ETC, E_S_OBJECTID_P_ETC_TREE7, "obj/Props/Etc/C36_Tree", "wintertree01_[0]_Stand_2641.obj", (float)7 / 8, (float)10 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_PROPS, E_M_OBJECTID_P_ETC, E_S_OBJECTID_P_ETC_TREE8, "obj/Props/Etc/C37_Tree", "wintertree02_[0]_Stand_2886.obj", 0, (float)11 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_PROPS, E_M_OBJECTID_P_ETC, E_S_OBJECTID_P_ETC_ROCK1, "obj/Props/Etc/C39_Rock", "snowytowerrock01_[0]_Stand_12.obj", (float)1 / 8, (float)11 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_PROPS, E_M_OBJECTID_P_ETC, E_S_OBJECTID_P_ETC_ROCK2, "obj/Props/Etc/C40_Rock", "snowytowerrock03_[0]_Stand_31.obj", (float)2 / 8, (float)11 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_PROPS, E_M_OBJECTID_P_ETC, E_S_OBJECTID_P_ETC_ROCK3, "obj/Props/Etc/C41_Rock", "tanarisrock_twilight_04_[0]_Stand_2235.obj", (float)3 / 8, (float)11 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_PROPS, E_M_OBJECTID_P_ETC, E_S_OBJECTID_P_ETC_ROCK4, "obj/Props/Etc/C42_Rock", "hyjalrock02_[0]_Stand_2485.obj", (float)4 / 8, (float)11 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_PROPS, E_M_OBJECTID_P_ETC, E_S_OBJECTID_P_ETC_BENCH1, "obj/Props/Etc/C43_Bench", "orcbench01_[0]_Stand_2454.obj", (float)5 / 8, (float)11 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_PROPS, E_M_OBJECTID_P_ETC, E_S_OBJECTID_P_ETC_BENCH2, "obj/Props/Etc/C44_Bench", "darkironworkbench02_[0]_Stand_2341.obj", (float)6 / 8, (float)11 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_PROPS, E_M_OBJECTID_P_ETC, E_S_OBJECTID_P_ETC_BUSH1, "obj/Props/Etc/C56_Bush", "bush_arthastears_[0]_Stand_500.obj", (float)7 / 8, (float)11 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_PROPS, E_M_OBJECTID_P_ETC, E_S_OBJECTID_P_ETC_BUSH2, "obj/Props/Etc/C57_Bush", "bush_bloodthistle_[0]_Stand_1266.obj", 0, (float)12 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_PROPS, E_M_OBJECTID_P_ETC, E_S_OBJECTID_P_ETC_BUSH3, "obj/Props/Etc/C58_Bush", "bush_dreamfoil_[0]_Stand_3032.obj", (float)1 / 8, (float)12 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_PROPS, E_M_OBJECTID_P_ETC, E_S_OBJECTID_P_ETC_BUSH4, "obj/Props/Etc/C61_Bush", "winterspringbush01_[0]_Stand_1813.obj", (float)2 / 8, (float)12 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_PROPS, E_M_OBJECTID_P_ETC, E_S_OBJECTID_P_ETC_BUSH5, "obj/Props/Etc/C62_Bush", "moongladebush02_[0]_Stand_1031.obj", (float)3 / 8, (float)12 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_PROPS, E_M_OBJECTID_P_ETC, E_S_OBJECTID_P_ETC_BUSH6, "obj/Props/Etc/C63_Bush", "kalidarbush01_[0]_Stand_0.obj", (float)4 / 8, (float)12 / 16));

	// Village					
	Add(new ST_OBJECTDATA(E_L_OBJECTID_VILLAGE, E_M_OBJECTID_V_VILLAGE, E_S_OBJECTID_V_STORMWIND, "obj/Village/Stormwind", "stormwind.obj", 0, (float)13 / 16));;
	Add(new ST_OBJECTDATA(E_L_OBJECTID_VILLAGE, E_M_OBJECTID_V_VILLAGE, E_S_OBJECTID_V_TOLVIR, "obj/Village/Tolvir", "tolvir_city_01.obj", (float)1 / 8, (float)13 / 16));;

	// NPC
	Add(new ST_OBJECTDATA(E_L_OBJECTID_NPC, E_M_OBJECTID_N_HUMAN,	E_S_OBJECTID_N_H_NPC1,						"obj/Npc/Human/Weapon",								"Human_weapon.obj",											0,			(float)14 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_NPC, E_M_OBJECTID_N_HUMAN,	E_S_OBJECTID_N_H_NPC2,						"obj/Npc/Human/Armor",								"Human_armor.obj",									(float)1 / 8,		(float)14 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_NPC, E_M_OBJECTID_N_HUMAN,	E_S_OBJECTID_N_H_NPC3,						"obj/Npc/Human/Stuff",								"humanfemalepeasant.obj",							(float)2 / 8,		(float)14 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_NPC,	E_M_OBJECTID_N_HUMAN,	E_S_OBJECTID_N_H_NPC4,						"obj/Npc/Human/Inn",								"humanfemalemerchantthin.obj",						(float)3 / 8,		(float)14 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_NPC,	E_M_OBJECTID_N_HUMAN,	E_S_OBJECTID_N_H_NPC5,						"obj/Npc/Human/Recruit",							"humanmalewarriormedium.obj",						(float)4 / 8,		(float)14 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_NPC,	E_M_OBJECTID_N_HUMAN,	E_S_OBJECTID_N_H_NPC6,						"obj/Npc/Human/Resident1",							"humanmalefarmer.obj",								(float)4 / 8,		(float)13 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_NPC,	E_M_OBJECTID_N_HUMAN,	E_S_OBJECTID_N_H_NPC7,						"obj/Npc/Human/Resident2",							"humanfemalekid.obj",								(float)5 / 8,		(float)13 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_NPC,	E_M_OBJECTID_N_HUMAN,	E_S_OBJECTID_N_H_NPC8,						"obj/Npc/Human/Resident3",							"humanmalepeasantgold.obj",							(float)6 / 8,		(float)13 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_NPC,	E_M_OBJECTID_N_HUMAN,	E_S_OBJECTID_N_H_NPC9,						"obj/Npc/Human/Resident4",							"humanmalekid.obj",									(float)7 / 8,		(float)13 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_NPC,	E_M_OBJECTID_N_ORC, 	E_S_OBJECTID_N_O_NPC1,						"obj/Npc/Orc/Weapon",								"felorc_sword.obj",											0,			(float)15 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_NPC,	E_M_OBJECTID_N_ORC, 	E_S_OBJECTID_N_O_NPC2,						"obj/Npc/Orc/Armor",								"orcmalewarriorlight.obj",							(float)1 / 8,		(float)15 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_NPC,	E_M_OBJECTID_N_ORC, 	E_S_OBJECTID_N_O_NPC3,						"obj/Npc/Orc/Stuff",								"orcmalekidgruntling_bp.obj",						(float)2 / 8,		(float)15 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_NPC,	E_M_OBJECTID_N_ORC, 	E_S_OBJECTID_N_O_NPC4,						"obj/Npc/Orc/Inn",									"orcmalemerchantlight.obj",							(float)3 / 8,		(float)15 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_NPC,	E_M_OBJECTID_N_ORC, 	E_S_OBJECTID_N_O_NPC5,						"obj/Npc/Orc/Recruit",								"rexxar.obj",										(float)4 / 8,		(float)15 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_NPC,	E_M_OBJECTID_N_ORC, 	E_S_OBJECTID_N_O_NPC6,						"obj/Npc/Orc/Resident1",							"orcfemalekid.obj",									(float)5 / 8,		(float)14 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_NPC,	E_M_OBJECTID_N_ORC, 	E_S_OBJECTID_N_O_NPC7,						"obj/Npc/Orc/Resident2",							"orcmalekid.obj",									(float)6 / 8,		(float)14 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_NPC,	E_M_OBJECTID_N_ORC, 	E_S_OBJECTID_N_O_NPC8,						"obj/Npc/Orc/Resident3",							"shaman_thrall.obj",								(float)7 / 8,		(float)14 / 16));


	// 쓰레기값																																																
	Add(new ST_OBJECTDATA(E_L_OBJECTID_START, E_M_OBJECTID_H_START, E_S_OBJECTID_BLANK, " ", " ", (float)7 / 8, (float)7 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_START, E_M_OBJECTID_H_START, E_S_OBJECTID_BLANK2, " ", " ", (float)7 / 8, (float)7 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_START, E_M_OBJECTID_H_START, E_S_OBJECTID_BLANK3, " ", " ", (float)7 / 8, (float)7 / 16));
	Add(new ST_OBJECTDATA(E_L_OBJECTID_START, E_M_OBJECTID_H_START, E_S_OBJECTID_BLANK4, " ", " ", (float)7 / 8, (float)7 / 16));
}

void cObjectDB::Add(ST_OBJECTDATA* pData)
{
	if (m_mapObject.find(pData->eSmallID) == m_mapObject.end())
	{
		m_mapObject[pData->eSmallID] = pData;
	}
}

void cObjectDB::Destroy()
{
	for each(auto it in m_mapObject)
	{
		SAFE_DELETE(it.second);
	}
	m_mapObject.clear();
	//delete this;
}