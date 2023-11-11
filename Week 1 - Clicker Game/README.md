## Clicker Game

This is week 1 of Project-a-week (PAW) which is a simple clicker game. The backend Express server uses bcrypt to securely hash plain text passwords
into hashes which are stored in a MongoDB instance. User sessions are preserved with JSON Web Tokens (JWTs) which are stored client-side in the
browser and are sent with each subsequent http request after a successful login.