# Week 12 of Paw - Last League Game

Single page application created with Vue that displays the player's last given League of Legends game.

## Set up
1. Clone the repository with `git clone https://github.com/RaymoZou/project-a-week.git` and navigate to this week's project.
2. Run `npm install` to install node dependencies.
3. Run `npm run dev` to start the Vue application.

## How To Use
Once the application is loaded, get your api key at Riot's Developer website [here](https://developer.riotgames.com/). You will
need it to enter and use in the application (Note: Riot issues personal API keys for small, personal projects. You'll have to apply
for a developer key). After that, enter your PUUID to view your last played game.

## Getting your PUUID
You can find your PUUID at the following endpoint `https://americas.api.riotgames.com/riot/account/v1/accounts/by-riot-id/{YOUR_GAME_NAME}/{YOUR_TAG_LINE}?api_key={YOUR_API_KEY}`

## Features
- Data fetching from Riot API endpoints using axios
- Cookie storing using the js-cookie
