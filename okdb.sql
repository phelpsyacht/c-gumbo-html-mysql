
CREATE DATABASE IF NOT EXISTS `book` ;
USE `book`;


CREATE TABLE IF NOT EXISTS `book_catalog` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `charpter_name` varchar(255) DEFAULT NULL,
  `book_id` char(5) DEFAULT NULL,
  `done` TINYINT(1) DEFAULT 0,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE IF NOT EXISTS `book_name` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `book_name` varchar(255) DEFAULT NULL,
  `folder` varchar(255) DEFAULT NULL,
  `done` TINYINT(1) NOT NULL DEFAULT 0,
  `ctime` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
