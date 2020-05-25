SELECT title FROM movies WHERE id IN
(SELECT movies.id FROM movies JOIN stars ON movies.id=stars.movie_id JOIN people ON people.id = stars.person_id WHERE people.name LIKE "Johnny Depp")
AND id IN (SELECT movies.id FROM movies JOIN stars ON movies.id=stars.movie_id JOIN people ON people.id = stars.person_id WHERE people.name LIKE "Helena Bonham Carter")