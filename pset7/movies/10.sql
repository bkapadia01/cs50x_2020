SELECT name FROM movies JOIN directors ON movies.id=directors.movie_id JOIN people ON people.id=directors.person_id JOIN ratings ON ratings.movie_id=movies.id WHERE rating>=9.0