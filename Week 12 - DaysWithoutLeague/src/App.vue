<!-- using the Options API  -->
<script lang="ts">
import axios from 'axios';
import { fromUnixTime } from 'date-fns'

export default {

	data() {
		return {
			lastGame: null,
			puuid: null,
			gameName: null,
			tagLine: null,
		}
	},

	computed: {
		// convert unix time to readable format
		// TODO: replace with actual time
		lastPlayed() { return this.lastGame ? fromUnixTime(this.lastGame.info.gameCreation / 1000) : "NOT LOADED" }
	},

	methods: {
		async getData() {
		// TODO: game name + tag line -> puuid -> last game played
			// this.puuid = await axios.get(`https://americas.api.riotgames.com/riot/account/v1/accounts/by-riot-id/${this.gameName}/${this.tagLine}?api_key=${import.meta.env.VITE_RITO_API}`)
			// var test = await axios.get(`https://americas.api.riotgames.com/riot/account/v1/accounts/by-riot-id/vwls/hehe?api_key=RGAPI-f1851ec3-61dc-47f2-b14a-11b534e8ff24`)
			const response = await axios.get(`https://americas.api.riotgames.com/lol/match/v5/matches/by-puuid/${this.puuid}/ids?start=0&count=1&api_key=${import.meta.env.VITE_RITO_API}`)
			const matchId = response.data
			const gameInfo = await axios.get(`https://americas.api.riotgames.com/lol/match/v5/matches/${matchId}?api_key=${import.meta.env.VITE_RITO_API}`)
			this.lastGame = gameInfo.data
			// console.log(gameInfo.data.info.gameCreation)
		},

		handleSubmit(e: Event) {
			e.preventDefault()
			// gameName and tagLine should != null at this point
			this.getData();
		}
	},

}
</script>

<template>
	<h1>Last League of Legends Game</h1>
	<!-- <p>last game created (in unix time): {{ lastGame ? lastGame.info.gameCreation : "loading..." }}</p> -->
	<form @submit="handleSubmit">
		<input type="text" v-model="puuid" placeholder="puuid" required>
		<!-- <input type="text" v-model="gameName" placeholder="gameName" required> -->
		<!-- <input type="text" v-model="tagLine" placeholder="tagLine" required> -->
		<button>submit</button>
	</form>
	<p><strong>Last game of League of Legends played on:</strong> {{ lastPlayed }}</p>
	<p>{{ puuid ? puuid : "puid not loaded" }}</p>
</template>
