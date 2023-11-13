## JWT Login Application

This is week 1 of Project-a-week (PAW) which is a simple user login application implemented with JSON Web Tokens. The backend Express server uses bcrypt to securely hash plain text passwords
into hashes which are stored in a MongoDB instance. User sessions are preserved with JSON Web Tokens (JWTs) which are stored client-side in the
browser (localStorage) which allow for them to be sent to subsequent http requests after a successful login.

# Features
- Signup with a username and password
- Login with username and password
- Check authentication state

