# Typescript Todo

Week 2 of PAW. Expanding upon my TypeScript skills with a simple TODO list app with a cli interface. A local PostgreSQL instance is required for the application to work.

## Set up
1. Clone the repository with `git clone https://github.com/RaymoZou/project-a-week.git` and navigate to this week's project.
2. Create a `.env` file in the root directory with the following fields:
   ```
   PGUSER={}
   PGPASSWORD={}
   PGHOST={}
   PGDATABASE={}
   PGPORT={}
   ```
3. Run `npm install` to install node dependencies.
4. Compile the typescript files with `tsc` and navigate to the `build` directory to start the application.

## Features
- Create and store a TODO using postgreSQL
