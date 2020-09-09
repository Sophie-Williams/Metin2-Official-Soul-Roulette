SET FOREIGN_KEY_CHECKS=0;
DROP TABLE IF EXISTS `soul_roulette_log`;
CREATE TABLE `soul_roulette_log`  (
  `name` varchar(12) CHARACTER SET big5 COLLATE big5_chinese_ci NOT NULL DEFAULT 'NONAME',
  `vnum` int(11) NOT NULL DEFAULT 0,
  `count` smallint(3) NOT NULL DEFAULT 1,
  `state` enum('OK','ERROR') CHARACTER SET big5 COLLATE big5_chinese_ci NULL DEFAULT 'OK',
  `date` datetime(0) NOT NULL
) ENGINE = InnoDB CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = Dynamic;
