drop table if exists etudiant;

create table etudiant (
	etuNum tinyint primary key auto_increment,
	etuNom varchar(30),
	etuPrenom varchar(30),
	etuSpe varchar(4)
	)
