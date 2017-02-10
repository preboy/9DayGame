/*
Navicat MySQL Data Transfer

Source Server         : 本机
Source Server Version : 50525
Source Host           : 127.0.0.1:3306
Source Database       : account_db

Target Server Type    : MYSQL
Target Server Version : 50525
File Encoding         : 65001

Date: 2012-09-02 22:13:30
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `account`
-- ----------------------------
DROP TABLE IF EXISTS `account`;
CREATE TABLE `account` (
`AccountID`  int(10) NOT NULL AUTO_INCREMENT ,
`AccountName`  varchar(32) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL ,
`Email`  varchar(32) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL ,
`Passwd`  varchar(32) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL ,
PRIMARY KEY (`AccountID`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
AUTO_INCREMENT=3

;

-- ----------------------------
-- Records of account
-- ----------------------------
BEGIN;
INSERT INTO `account` VALUES ('1', 'zcg', 'preboy@126.com', 'zhang'), ('2', 'dx', 'dx@126.com', 'dx');
COMMIT;

-- ----------------------------
-- Auto increment value for `account`
-- ----------------------------
ALTER TABLE `account` AUTO_INCREMENT=3;
