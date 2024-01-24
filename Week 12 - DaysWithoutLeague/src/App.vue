<!-- using the Options API  -->
<script lang="ts">
import axios from 'axios';
import { fromUnixTime } from 'date-fns'

export default {

	data() {
		return {
			lastGame: null
		}
	},

	computed: {
		// convert unix time to readable format
		lastPlayed() { return this.lastGame ? fromUnixTime(1705876957690 / 1000) : "NOT LOADED" }
	},

	methods: {
		async getData() {
		// TODO: user input of PUUID (currently set in .env)
			const response = await axios.get(`https://americas.api.riotgames.com/lol/match/v5/matches/by-puuid/${import.meta.env.VITE_PUUID}/ids?start=0&count=1&api_key=${import.meta.env.VITE_RITO_API}`)
			const matchId = response.data
			const gameInfo = await axios.get(`https://americas.api.riotgames.com/lol/match/v5/matches/${matchId}?api_key=${import.meta.env.VITE_RITO_API}`)
			this.lastGame = gameInfo.data
		},
	},

	mounted() {
		this.getData()
	},
}
</script>

<template>
	<h1>Last League of Legends Game</h1>
	<!-- <p>last game created (in unix time): {{ lastGame ? lastGame.info.gameCreation : "loading..." }}</p> -->
	<p><strong>Last game of League of Legends played on:</strong> {{ lastPlayed }}</p>
</template>
