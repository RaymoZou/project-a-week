import express from 'express';
import dotenv from 'dotenv';
import { router } from './router';
dotenv.config();

const app = express();
app.use('/api', router)

console.log('sd');

app.listen(process.env.PORT || 3000, () => {
    console.log(`listening on port ${process.env.PORT || 3000}`);
});

