-- phpMyAdmin SQL Dump
-- version 4.7.1
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Generation Time: Aug 17, 2017 at 02:31 AM
-- Server version: 5.7.16-log
-- PHP Version: 7.1.6

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `demobox`
--

-- --------------------------------------------------------

--
-- Table structure for table `cloudupdate`
--

DROP TABLE IF EXISTS `cloudupdate`;
CREATE TABLE `cloudupdate` (
  `id` int(11) NOT NULL,
  `CustId` int(11) DEFAULT NULL COMMENT 'Customer',
  `SQLString` longtext COMMENT 'SQL string to execute to webPortal',
  `DatePosted` datetime DEFAULT NULL,
  `posted` int(1) DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `customer`
--

DROP TABLE IF EXISTS `customer`;
CREATE TABLE `customer` (
  `id` int(11) NOT NULL,
  `username` varchar(20) DEFAULT NULL,
  `password` varchar(128) DEFAULT NULL,
  `activkey` varchar(128) DEFAULT NULL,
  `companyName` varchar(255) DEFAULT NULL,
  `address` varchar(200) DEFAULT NULL,
  `telNo` varchar(45) DEFAULT NULL,
  `faxNo` varchar(45) DEFAULT NULL,
  `email` varchar(45) DEFAULT NULL,
  `contactPerson` varchar(45) DEFAULT NULL,
  `status` int(1) DEFAULT NULL,
  `notes` text,
  `jobOrderLabel` varchar(25) DEFAULT NULL,
  `address3` varchar(100) DEFAULT NULL,
  `address2` varchar(100) DEFAULT NULL,
  `address1` varchar(100) DEFAULT NULL,
  `registrationCode` varchar(50) DEFAULT NULL,
  `registrationId` varchar(50) DEFAULT NULL,
  `createAt` timestamp NULL DEFAULT NULL ON UPDATE CURRENT_TIMESTAMP,
  `lastvisitAt` timestamp NULL DEFAULT NULL ON UPDATE CURRENT_TIMESTAMP,
  `superuser` int(1) DEFAULT NULL,
  `soapId` int(11) DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `employees`
--

DROP TABLE IF EXISTS `employees`;
CREATE TABLE `employees` (
  `id` int(11) NOT NULL,
  `userId` varchar(20) NOT NULL,
  `firstName` varchar(25) DEFAULT NULL,
  `middleName` varchar(25) DEFAULT NULL,
  `lastName` varchar(25) DEFAULT NULL,
  `extName` varchar(25) DEFAULT NULL,
  `address1` varchar(100) DEFAULT NULL,
  `address2` varchar(100) DEFAULT NULL,
  `address3` varchar(100) DEFAULT NULL,
  `deptCode` varchar(20) DEFAULT NULL,
  `position` varchar(50) DEFAULT NULL,
  `email` varchar(200) DEFAULT NULL,
  `faceImage` varchar(200) DEFAULT NULL,
  `mobileNumber` varchar(20) DEFAULT NULL,
  `custId` int(11) DEFAULT NULL,
  `createDate` date DEFAULT NULL,
  `createTime` time DEFAULT NULL,
  `isUser` int(11) DEFAULT NULL,
  `cribId` varchar(50) NOT NULL,
  `isUserKab` int(11) DEFAULT NULL,
  `isUserCrib` int(11) DEFAULT NULL,
  `isUserPorta` int(11) DEFAULT NULL,
  `username` varchar(20) NOT NULL,
  `password` varchar(200) NOT NULL,
  `userRole` int(11) NOT NULL,
  `lastvisit` date NOT NULL,
  `disabled` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `itemkabdrawerbins`
--

DROP TABLE IF EXISTS `itemkabdrawerbins`;
CREATE TABLE `itemkabdrawerbins` (
  `id` int(11) NOT NULL,
  `binId` varchar(50) NOT NULL,
  `drawerId` varchar(25) DEFAULT NULL,
  `kabId` varchar(20) DEFAULT NULL,
  `custId` int(11) DEFAULT NULL,
  `itemId` varchar(25) DEFAULT NULL,
  `prevstatus` int(11) DEFAULT '1',
  `status` int(11) DEFAULT '0',
  `toolNumber` int(11) NOT NULL,
  `drawerNum` int(11) NOT NULL,
  `missing` int(11) DEFAULT NULL COMMENT 'Missing Indicator',
  `imageNormal` varchar(200) DEFAULT NULL,
  `imageActive` varchar(200) DEFAULT NULL,
  `imageOut` varchar(200) DEFAULT NULL,
  `cleft` float(10,2) DEFAULT '0.00',
  `ctop` float(10,2) DEFAULT '0.00',
  `visible` int(2) DEFAULT '1',
  `blockIndex` int(11) DEFAULT NULL,
  `angle` float(50,2) DEFAULT NULL,
  `width` float(10,2) DEFAULT NULL,
  `height` float(10,2) DEFAULT NULL,
  `currentCalibrationDate` date DEFAULT NULL,
  `lastCalibrationDate` date DEFAULT NULL,
  `calibration` int(1) DEFAULT '0',
  `calInterval` int(11) DEFAULT NULL,
  `serviceable` int(11) NOT NULL DEFAULT '1',
  `serialNumber` varchar(50) NOT NULL,
  `flip` int(11) DEFAULT '0',
  `reverse` int(11) DEFAULT '0',
  `calibrated` int(11) NOT NULL,
  `transferred` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `itemkabdrawers`
--

DROP TABLE IF EXISTS `itemkabdrawers`;
CREATE TABLE `itemkabdrawers` (
  `id` int(11) NOT NULL,
  `drawerId` varchar(20) NOT NULL,
  `kabId` varchar(50) DEFAULT NULL,
  `lockCode` varchar(20) DEFAULT NULL,
  `status` int(11) DEFAULT NULL,
  `remarks` varchar(255) DEFAULT NULL,
  `createdDate` date DEFAULT NULL,
  `createdTime` time DEFAULT NULL,
  `lastAccess` date DEFAULT NULL,
  `lastAccessTime` time DEFAULT NULL,
  `custId` int(11) DEFAULT NULL,
  `drawerCode` int(11) DEFAULT NULL,
  `indexCode` int(11) DEFAULT NULL,
  `layout` varchar(255) DEFAULT NULL,
  `lightStatus` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `itemkabs`
--

DROP TABLE IF EXISTS `itemkabs`;
CREATE TABLE `itemkabs` (
  `id` int(11) NOT NULL,
  `kabId` varchar(20) NOT NULL,
  `description` varchar(255) DEFAULT NULL,
  `location` varchar(255) DEFAULT NULL,
  `createdDate` datetime DEFAULT NULL,
  `createdTime` datetime DEFAULT NULL,
  `lastAccess` datetime DEFAULT NULL,
  `lastAccessTime` datetime DEFAULT NULL,
  `userId` int(11) DEFAULT NULL,
  `modelNumber` varchar(50) DEFAULT NULL,
  `custId` int(11) DEFAULT NULL,
  `assigned` int(1) DEFAULT '0',
  `numberDrawers` int(11) DEFAULT NULL,
  `numberBins` int(11) DEFAULT NULL,
  `drawersLocked` int(11) DEFAULT NULL,
  `firmwareVersion` varchar(100) DEFAULT NULL,
  `notes` text,
  `serialNumber` varchar(200) DEFAULT NULL,
  `expiration` int(11) DEFAULT NULL,
  `locationId` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `jobs`
--

DROP TABLE IF EXISTS `jobs`;
CREATE TABLE `jobs` (
  `trailId` int(11) NOT NULL,
  `description` varchar(150) DEFAULT NULL,
  `custId` int(11) DEFAULT NULL,
  `startDate` date DEFAULT NULL,
  `endDate` date DEFAULT NULL,
  `remark` varchar(255) DEFAULT NULL,
  `continues` int(11) DEFAULT NULL,
  `speeddial` int(11) NOT NULL,
  `disabled` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `kabemployeeitemtransactions`
--

DROP TABLE IF EXISTS `kabemployeeitemtransactions`;
CREATE TABLE `kabemployeeitemtransactions` (
  `id` int(11) NOT NULL,
  `transId` varchar(50) NOT NULL,
  `userId` varchar(30) DEFAULT NULL,
  `transType` int(11) DEFAULT NULL,
  `itemId` varchar(50) DEFAULT NULL,
  `transDate` date DEFAULT NULL,
  `transTime` time DEFAULT NULL,
  `remarks` varchar(255) DEFAULT NULL,
  `trailId` varchar(20) DEFAULT NULL,
  `custId` int(11) DEFAULT NULL,
  `drawerNum` int(11) DEFAULT NULL,
  `toolNum` int(11) DEFAULT NULL,
  `kabId` varchar(11) DEFAULT NULL,
  `confirmed` int(11) DEFAULT NULL,
  `inDate` date DEFAULT NULL,
  `outDate` date DEFAULT NULL,
  `WO` varchar(20) DEFAULT NULL,
  `BN` varchar(20) DEFAULT NULL,
  `inTime` time DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `kabemployeeitemtransactions_history`
--

DROP TABLE IF EXISTS `kabemployeeitemtransactions_history`;
CREATE TABLE `kabemployeeitemtransactions_history` (
  `id` int(11) NOT NULL,
  `transId` varchar(50) NOT NULL,
  `userId` varchar(30) DEFAULT NULL,
  `transType` int(11) DEFAULT NULL,
  `itemId` varchar(50) DEFAULT NULL,
  `transDate` date DEFAULT NULL,
  `transTime` time DEFAULT NULL,
  `remarks` varchar(255) DEFAULT NULL,
  `trailId` varchar(20) DEFAULT NULL,
  `custId` int(11) DEFAULT NULL,
  `drawerNum` int(11) DEFAULT NULL,
  `toolNum` int(11) DEFAULT NULL,
  `kabId` varchar(11) DEFAULT NULL,
  `confirmed` int(11) DEFAULT NULL,
  `inDate` date DEFAULT NULL,
  `outDate` date DEFAULT NULL,
  `WO` varchar(20) DEFAULT NULL,
  `BN` varchar(20) DEFAULT NULL,
  `inTime` time DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `kabtransactionlog`
--

DROP TABLE IF EXISTS `kabtransactionlog`;
CREATE TABLE `kabtransactionlog` (
  `id` int(11) NOT NULL,
  `transId` varchar(50) NOT NULL,
  `userId` varchar(30) DEFAULT NULL,
  `transType` int(11) DEFAULT NULL,
  `itemId` varchar(50) DEFAULT NULL,
  `transDate` date DEFAULT NULL,
  `transTime` time DEFAULT NULL,
  `remarks` varchar(255) DEFAULT NULL,
  `trailId` varchar(20) DEFAULT NULL,
  `custId` int(11) DEFAULT NULL,
  `drawerNum` int(11) DEFAULT NULL,
  `toolNum` int(11) DEFAULT NULL,
  `kabId` varchar(11) DEFAULT NULL,
  `inDate` date DEFAULT NULL,
  `outDate` date DEFAULT NULL,
  `WO` varchar(20) DEFAULT NULL,
  `BN` varchar(20) DEFAULT NULL,
  `transStatus` int(11) DEFAULT '0' COMMENT 'TransStatus = 0 Failed TransStatus\r\n= 1 Success'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `location`
--

DROP TABLE IF EXISTS `location`;
CREATE TABLE `location` (
  `id` int(11) NOT NULL,
  `custId` int(11) DEFAULT NULL,
  `description` varchar(200) DEFAULT NULL,
  `code` varchar(50) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `soapuser`
--

DROP TABLE IF EXISTS `soapuser`;
CREATE TABLE `soapuser` (
  `id` int(11) NOT NULL,
  `username` varchar(20) DEFAULT NULL,
  `password` varchar(10) DEFAULT NULL,
  `companyname` varchar(100) DEFAULT NULL,
  `email` varchar(200) DEFAULT NULL,
  `dateCreated` datetime DEFAULT NULL,
  `lastAccess` datetime DEFAULT NULL,
  `contactno` varchar(20) DEFAULT NULL,
  `contactperson` varchar(50) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `toolcategories`
--

DROP TABLE IF EXISTS `toolcategories`;
CREATE TABLE `toolcategories` (
  `catId` int(11) NOT NULL,
  `description` varchar(100) DEFAULT NULL,
  `custId` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `tools`
--

DROP TABLE IF EXISTS `tools`;
CREATE TABLE `tools` (
  `id` int(11) NOT NULL,
  `PartNo` varchar(20) NOT NULL,
  `description` varchar(100) DEFAULT NULL,
  `catId` varchar(20) DEFAULT NULL,
  `subCatId` int(11) DEFAULT NULL,
  `latestCost` float(8,2) DEFAULT NULL,
  `serialNo` varchar(25) DEFAULT NULL,
  `custId` int(11) DEFAULT NULL,
  `supplierId` int(11) DEFAULT NULL,
  `assigned` int(11) DEFAULT NULL,
  `stockcode` varchar(50) DEFAULT NULL,
  `image_b` varchar(255) DEFAULT NULL,
  `image_r` varchar(255) DEFAULT NULL,
  `image_g` varchar(255) DEFAULT NULL,
  `ispresent` int(11) DEFAULT NULL,
  `serial` varchar(255) DEFAULT NULL,
  `isKit` int(11) DEFAULT '0',
  `image_w` varchar(255) DEFAULT NULL,
  `B` int(11) DEFAULT NULL,
  `G` int(11) DEFAULT NULL,
  `R` int(11) DEFAULT NULL,
  `W` int(11) DEFAULT NULL,
  `kitcount` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `transfertool`
--

DROP TABLE IF EXISTS `transfertool`;
CREATE TABLE `transfertool` (
  `id` int(11) NOT NULL,
  `returned` int(11) DEFAULT '0',
  `fromKabId` varchar(50) DEFAULT NULL,
  `fromDrawernum` int(11) DEFAULT NULL,
  `fromToolnum` int(11) DEFAULT NULL,
  `toKabId` varchar(50) DEFAULT NULL,
  `inDate` date DEFAULT NULL,
  `outDate` date DEFAULT NULL,
  `userid` varchar(255) DEFAULT NULL,
  `trailId` int(11) DEFAULT NULL,
  `transType` int(11) DEFAULT NULL,
  `destKabId` varchar(50) DEFAULT NULL,
  `destDrawernum` int(11) DEFAULT NULL,
  `destToolnum` int(11) DEFAULT NULL,
  `custId` int(11) DEFAULT NULL,
  `kabId` varchar(20) NOT NULL,
  `transferType` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
CREATE TABLE `users` (
  `id` int(11) NOT NULL,
  `enabledCrib` int(11) NOT NULL,
  `userId` varchar(20) NOT NULL,
  `pin` varchar(255) NOT NULL,
  `fullName` varchar(50) DEFAULT NULL,
  `enabled` int(11) DEFAULT NULL,
  `enabledPorta` int(11) DEFAULT NULL,
  `enabledKab` int(11) DEFAULT NULL,
  `createdDate` datetime DEFAULT NULL,
  `lastAccess_porta` datetime DEFAULT NULL,
  `lastAccess_kab` datetime DEFAULT NULL,
  `lastAccTime` datetime DEFAULT NULL,
  `createdTime` datetime DEFAULT NULL,
  `accessCountKab` int(11) NOT NULL,
  `accessCountPorta` int(11) DEFAULT NULL,
  `custId` int(11) DEFAULT NULL,
  `accessTypePorta` int(255) DEFAULT NULL,
  `accessTypeKab` int(11) NOT NULL,
  `scaleId` varchar(50) DEFAULT NULL,
  `kabId` varchar(20) DEFAULT NULL,
  `faceImage` varchar(200) DEFAULT NULL,
  `email` varchar(255) DEFAULT NULL,
  `username` varchar(20) DEFAULT NULL,
  `password` varchar(128) DEFAULT NULL,
  `activkey` varchar(128) DEFAULT NULL,
  `createAt` timestamp NULL DEFAULT NULL ON UPDATE CURRENT_TIMESTAMP,
  `lastvisitAt` datetime DEFAULT NULL,
  `superuser` int(1) DEFAULT NULL,
  `status` int(1) DEFAULT NULL,
  `kabtrak` int(11) DEFAULT NULL,
  `portatrak` int(11) DEFAULT NULL,
  `lastAccessCrib` datetime NOT NULL,
  `accessCountCrib` int(11) DEFAULT NULL,
  `accessTypeCrib` int(11) NOT NULL,
  `contactno` varchar(50) NOT NULL,
  `cribtrak` int(11) DEFAULT NULL,
  `cribId` varchar(50) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `cloudupdate`
--
ALTER TABLE `cloudupdate`
  ADD PRIMARY KEY (`id`),
  ADD KEY `fk_custid_idx` (`CustId`);

--
-- Indexes for table `customer`
--
ALTER TABLE `customer`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `employees`
--
ALTER TABLE `employees`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `itemkabdrawerbins`
--
ALTER TABLE `itemkabdrawerbins`
  ADD PRIMARY KEY (`id`),
  ADD KEY `fk_kabid_idx` (`kabId`),
  ADD KEY `fk_custid_idx` (`custId`);

--
-- Indexes for table `itemkabdrawers`
--
ALTER TABLE `itemkabdrawers`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `itemkabs`
--
ALTER TABLE `itemkabs`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `jobs`
--
ALTER TABLE `jobs`
  ADD PRIMARY KEY (`trailId`);

--
-- Indexes for table `kabemployeeitemtransactions`
--
ALTER TABLE `kabemployeeitemtransactions`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `kabemployeeitemtransactions_history`
--
ALTER TABLE `kabemployeeitemtransactions_history`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `kabtransactionlog`
--
ALTER TABLE `kabtransactionlog`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `location`
--
ALTER TABLE `location`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `soapuser`
--
ALTER TABLE `soapuser`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `toolcategories`
--
ALTER TABLE `toolcategories`
  ADD PRIMARY KEY (`catId`);

--
-- Indexes for table `tools`
--
ALTER TABLE `tools`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `transfertool`
--
ALTER TABLE `transfertool`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `cloudupdate`
--
ALTER TABLE `cloudupdate`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=656;
--
-- AUTO_INCREMENT for table `customer`
--
ALTER TABLE `customer`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;
--
-- AUTO_INCREMENT for table `employees`
--
ALTER TABLE `employees`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=403;
--
-- AUTO_INCREMENT for table `itemkabdrawerbins`
--
ALTER TABLE `itemkabdrawerbins`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8572;
--
-- AUTO_INCREMENT for table `itemkabdrawers`
--
ALTER TABLE `itemkabdrawers`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=203;
--
-- AUTO_INCREMENT for table `itemkabs`
--
ALTER TABLE `itemkabs`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;
--
-- AUTO_INCREMENT for table `jobs`
--
ALTER TABLE `jobs`
  MODIFY `trailId` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=178;
--
-- AUTO_INCREMENT for table `kabemployeeitemtransactions`
--
ALTER TABLE `kabemployeeitemtransactions`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=84;
--
-- AUTO_INCREMENT for table `kabemployeeitemtransactions_history`
--
ALTER TABLE `kabemployeeitemtransactions_history`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `kabtransactionlog`
--
ALTER TABLE `kabtransactionlog`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `location`
--
ALTER TABLE `location`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `soapuser`
--
ALTER TABLE `soapuser`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `toolcategories`
--
ALTER TABLE `toolcategories`
  MODIFY `catId` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `tools`
--
ALTER TABLE `tools`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8237;
--
-- AUTO_INCREMENT for table `transfertool`
--
ALTER TABLE `transfertool`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `users`
--
ALTER TABLE `users`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=302;
--
-- Constraints for dumped tables
--

--
-- Constraints for table `cloudupdate`
--
ALTER TABLE `cloudupdate`
  ADD CONSTRAINT `fk_custid` FOREIGN KEY (`CustId`) REFERENCES `customer` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
