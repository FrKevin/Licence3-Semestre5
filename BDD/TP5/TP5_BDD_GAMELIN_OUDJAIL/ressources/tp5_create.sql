--- by Ramakrishnan ----
drop tabledro if exists certifications;
drop table if exists vols;
drop table if exists avions;
drop table if exists employes;

CREATE TABLE avions(
aid int primary key,
anom varchar(30),
portee int);

INSERT INTO avions VALUES(1,'Boeing 747-400',8430);
INSERT INTO avions VALUES(2,'Boeing 737-800',3383);
INSERT INTO avions VALUES(3,'Airbus A340-300',7120);
INSERT INTO avions VALUES(4,'British Aerospace Jetstream 41',1502);
INSERT INTO avions VALUES(5,'Embraer ERJ-145',1530);
INSERT INTO avions VALUES(6,'SAAB 340',2128);
INSERT INTO avions VALUES(7,'Piper Archer III',520);
INSERT INTO avions VALUES(8,'Tupolev 154',4103);
INSERT INTO avions VALUES(9,'Lockheed L1011',6900);
INSERT INTO avions VALUES(10,'Boeing 757-300',4010);
INSERT INTO avions VALUES(11,'Boeing 777-300',6441);
INSERT INTO avions VALUES(12,'Boeing 767-400ER',6475);
INSERT INTO avions VALUES(13,'Airbus A320',2605);
INSERT INTO avions VALUES(14,'Airbus A319',1805);
INSERT INTO avions VALUES(15,'Boeing 727',1504);
INSERT INTO avions VALUES(16,'Airbus A380-800ER',18001);
INSERT INTO avions VALUES(17,'Schwitzer 2-33',30);


------------------------------------------------------------------
create table employes(
eid int primary key,
enom varchar(30),
salaire int
);

INSERT INTO employes VALUES(242518965,'Ivonne Boulala',120433);
INSERT INTO employes VALUES(141582651,'Anael Klein',178345);
INSERT INTO employes VALUES(011564812,'Joris Robillard',153972);
INSERT INTO employes VALUES(567354612,'Laura Giacco',256481);
INSERT INTO employes VALUES(552455318,'Patricia Jones',101745);
INSERT INTO employes VALUES(550156548,'Victor Goron',205187);
INSERT INTO employes VALUES(390487451,'Linda Mariencourt',212156);
INSERT INTO employes VALUES(274878974,'Valentin Owczarek',498950);
INSERT INTO employes VALUES(254099823,'Brahim Akouz',24450);
INSERT INTO employes VALUES(356187925,'Astelia Massamba',44740);
INSERT INTO employes VALUES(355548984,'Hugo Ermenidis',212156 );
INSERT INTO employes VALUES(310454876,'Boubacar Diallo',212156);
INSERT INTO employes VALUES(489456522,'Justin Dutoit',27984);
INSERT INTO employes VALUES(489221823,'Nadir Trabelsi',23980);
INSERT INTO employes VALUES(548977562,'Ulysses Boulala',84476);
INSERT INTO employes VALUES(310454877,'Ceyhun Ozugur',33546);
INSERT INTO employes VALUES(142519864,'Teresa Klatzer',227489);
INSERT INTO employes VALUES(269734834,'Ana Bozianu',289950);
INSERT INTO employes VALUES(287321212,'Mengmeng Zhao',48090);
INSERT INTO employes VALUES(552455348,'Rachid El Amrani',152013);
INSERT INTO employes VALUES(248965255,'Perrine Honore',43723);
INSERT INTO employes VALUES(159542516,'Maxence Gens',48250);
INSERT INTO employes VALUES(348121549,'Catalin Daniel Ramirez',32899);
INSERT INTO employes VALUES(090873519,'Hakim Taleb',32021);
INSERT INTO employes VALUES(486512566,'Simon Jeunechamp',43001);
INSERT INTO employes VALUES(619023588,'Jennifer Thomas',54921);
INSERT INTO employes VALUES(015645489,'Camille Girard',18050);
INSERT INTO employes VALUES(556784565,'Etienne Renard',205187);
INSERT INTO employes VALUES(573284895,'Tommy Carpentier',114323);
INSERT INTO employes VALUES(574489456,'Nicolas Baudin',105743);
INSERT INTO employes VALUES(574489457,'Oussama Moulana',20);

----------------------------------------------------------
create table certifications(
eid int references employes(eid),
aid int references avions(aid),
primary key (eid,aid)
);


INSERT INTO certifications VALUES(567354612,1);
INSERT INTO certifications VALUES(567354612,2);
INSERT INTO certifications VALUES(567354612,10);
INSERT INTO certifications VALUES(567354612,11);
INSERT INTO certifications VALUES(567354612,12);
INSERT INTO certifications VALUES(567354612,15);
INSERT INTO certifications VALUES(567354612,7);
INSERT INTO certifications VALUES(567354612,9);
INSERT INTO certifications VALUES(567354612,3);
INSERT INTO certifications VALUES(567354612,4);
INSERT INTO certifications VALUES(567354612,5);
INSERT INTO certifications VALUES(552455318,2);
INSERT INTO certifications VALUES(552455318,14);
INSERT INTO certifications VALUES(550156548,1);
INSERT INTO certifications VALUES(550156548,12);
INSERT INTO certifications VALUES(390487451,3);
INSERT INTO certifications VALUES(390487451,13);
INSERT INTO certifications VALUES(390487451,14);
INSERT INTO certifications VALUES(274878974,10);
INSERT INTO certifications VALUES(274878974,12);
INSERT INTO certifications VALUES(355548984,8);
INSERT INTO certifications VALUES(355548984,9);
INSERT INTO certifications VALUES(310454876,8);
INSERT INTO certifications VALUES(310454876,9);
INSERT INTO certifications VALUES(548977562,7);
INSERT INTO certifications VALUES(142519864,1);
INSERT INTO certifications VALUES(142519864,11);
INSERT INTO certifications VALUES(142519864,12);
INSERT INTO certifications VALUES(142519864,10);
INSERT INTO certifications VALUES(142519864,3);
INSERT INTO certifications VALUES(142519864,2);
INSERT INTO certifications VALUES(142519864,13);
INSERT INTO certifications VALUES(142519864,7);
INSERT INTO certifications VALUES(269734834,1);
INSERT INTO certifications VALUES(269734834,2);
INSERT INTO certifications VALUES(269734834,3);
INSERT INTO certifications VALUES(269734834,4);
INSERT INTO certifications VALUES(269734834,5);
INSERT INTO certifications VALUES(269734834,6);
INSERT INTO certifications VALUES(269734834,7);
INSERT INTO certifications VALUES(269734834,8);
INSERT INTO certifications VALUES(269734834,9);
INSERT INTO certifications VALUES(269734834,10);
INSERT INTO certifications VALUES(269734834,11);
INSERT INTO certifications VALUES(269734834,12);
INSERT INTO certifications VALUES(269734834,13);
INSERT INTO certifications VALUES(269734834,14);
INSERT INTO certifications VALUES(269734834,15);
INSERT INTO certifications VALUES(552455318,7);
INSERT INTO certifications VALUES(556784565,5);
INSERT INTO certifications VALUES(556784565,2);
INSERT INTO certifications VALUES(556784565,3);
INSERT INTO certifications VALUES(573284895,3);
INSERT INTO certifications VALUES(573284895,4);
INSERT INTO certifications VALUES(573284895,5);
INSERT INTO certifications VALUES(574489456,8);
INSERT INTO certifications VALUES(574489456,6);
INSERT INTO certifications VALUES(574489457,7);
INSERT INTO certifications VALUES(242518965,2);
INSERT INTO certifications VALUES(242518965,10);
INSERT INTO certifications VALUES(141582651,2);
INSERT INTO certifications VALUES(141582651,10);
INSERT INTO certifications VALUES(141582651,12);
INSERT INTO certifications VALUES(011564812,2);
INSERT INTO certifications VALUES(011564812,10);
INSERT INTO certifications VALUES(356187925,6);
INSERT INTO certifications VALUES(159542516,5);
INSERT INTO certifications VALUES(159542516,7);
INSERT INTO certifications VALUES(090873519,6);

------------------------------------------------------------------


create table vols(
vid int,
dep varchar(30),
arr varchar(30),
distance int,
h_dep timestamp,
h_arr timestamp,
prix real
);

INSERT INTO vols VALUES(99,'Los Angeles','Washington D.C.',2308,'2011-04-12 09:30','2011-04-12 21:40',235.98);
INSERT INTO vols VALUES(13,'Los Angeles','Chicago',1749,'2011-04-12 08:45','2011-04-12 20:45',220.98);
INSERT INTO vols VALUES(346,'Los Angeles','Dallas',1251,'2011-04-12 11:50','2011-04-12 19:05',225.43);
INSERT INTO vols VALUES(387,'Los Angeles','Boston',2606,'2011-04-12 07:03','2011-04-12 17:03',261.56);
INSERT INTO vols VALUES(7,'Los Angeles','Sydney',7487,'2011-04-12 22:30','2011-04-14 6:10',1278.56);
INSERT INTO vols VALUES(2,'Los Angeles','Tokyo',5478,'2011-04-12 12:30','2011-04-13 15:55',780.99);
INSERT INTO vols VALUES(33,'CDG','NOU',17000,'2011-04-12 09:15','2011-04-14 11:15',3750.23);
INSERT INTO vols VALUES(34,'CDG','NOU',17000,'2011-04-12 12:45','2011-04-14 15:18',4250.98);
INSERT INTO vols VALUES(76,'Chicago','Los Angeles',1749,'2011-04-12 08:32','2011-04-12 10:03',220.98);
INSERT INTO vols VALUES(68,'Chicago','New York',802,'2011-04-12 09:00','2011-04-12 12:02',202.45);
INSERT INTO vols VALUES(7789,'Madison','Detroit',319,'2011-04-12 06:15','2011-04-12 08:19',120.33);
INSERT INTO vols VALUES(701,'Detroit','New York',470,'2011-04-12 08:55','2011-04-12 10:26',180.56);
INSERT INTO vols VALUES(702,'Madison','New York',789,'2011-04-12 07:05','2011-04-12 10:12',202.34);
INSERT INTO vols VALUES(4884,'Madison','Chicago',84,'2011-04-12 22:12','2011-04-12 23:02',112.45);
INSERT INTO vols VALUES(2223,'Madison','Pittsburgh',517,'2011-04-12 08:02','2011-04-12 10:01',189.98);
INSERT INTO vols VALUES(5694,'Madison','Minneapolis',247,'2011-04-12 08:32','2011-04-12 09:33',120.11);
INSERT INTO vols VALUES(304,'Minneapolis','New York',991,'2011-04-12 10:00','2011-04-12 1:39',101.56);
INSERT INTO vols VALUES(149,'Pittsburgh','New York',303,'2011-04-12 09:42','2011-04-12 12:09',116.50);
