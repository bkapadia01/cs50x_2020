SELECT name FROM people WHERE id IN (SELECT person_id FROM stars WHERE movie_id IN (SELECT movie_id from movies JOIN stars ON movies.id=stars.movie_id JOIN people ON stars.person_id=people.id WHERE name LIKE "Kevin Bacon" AND birth = 1958))
EXCEPT 
SELECT name FROM people WHERE name LIKE "Kevin Bacon"