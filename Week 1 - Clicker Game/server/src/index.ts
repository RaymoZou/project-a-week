import dotenv from 'dotenv';
import express, { NextFunction, Request, Response } from 'express';
import { router } from './router';
import jwt from 'jsonwebtoken';
import mongoose from 'mongoose';
import { User } from './models/user';
import bcrypt from 'bcrypt';
import cors from 'cors';
dotenv.config();

const app = express();
// const corsOptions = {
//     origin: 'http://localhost:5173', // Replace with your client's origin
//     methods: 'GET,HEAD,PUT,PATCH,POST,DELETE',
//     credentials: true,
//     optionsSuccessStatus: 204,
// };

app.use(cors());

app.use(express.json());

// mongoose setup
// (mongoose buffers all the commands - don't have to wait for this connection)
mongoose.connect(process.env.MONGODB_URI as string);

const isAuthenticated = (req: Request, res: Response, next: NextFunction) => {
    const token = req.headers.authorization?.split(' ')[1];
    try {
        if (!token) return res.status(200).json({ message: 'no jwt token provided' });
        jwt.verify(token, process.env.SECRET_KEY as string, (err, decoded) => {
            if (err) throw err;
        });
        next();
    } catch (err) {
        next(err);
        return res.status(401).json({ message: "you are not authenticated" });
    }
};

app.post('/signup', async (req: Request, res: Response, next: NextFunction) => {
    console.log('POST request received');
    try {
        const username = req.body.username;
        const hash = await bcrypt.hash(req.body.password, 10);
        const user = new User({ username, hash });
        console.log(hash);
        await user.save();
        res.status(200).json({ message: "user saved" });
    } catch (err) {
        next(err);
    }
    next();
})

// return a jwt token if successful
app.post('/login', async (req: Request, res: Response, next: NextFunction) => {
    try {
        const username = req.body.username;
        const plainText = req.body.password;
        // query user
        const user = await User.findOne({ username: username });
        if (!user) throw new Error("user not found");
        const isValid = await bcrypt.compare(plainText, user.hash);
        if (isValid) {
            // generate jwt and store as cookie
            var token = jwt.sign({ username }, process.env.SECRET_KEY as string, {
                // 1 hour
                expiresIn: 60 * 60
            });
            res.cookie("jwt", token);
            res.status(200).json({ jwt: token });
            // res.status(200).json({ message: "valid" });
        } else {
            res.status(401).json({ message: "is not valid" });
        }
    } catch (err) {
        next(err);
    };


    // if (username === 'user' && password === 'pass') {
    //     var token = jwt.sign({ username }, process.env.SECRET_KEY as string, {
    //         // 1 hour
    //         expiresIn: 60 * 60
    //     });
    //     res.cookie("jwt", token);
    //     res.status(200).json({ jwt: token });
    // } else {
    //     res.status(401).json({ message: 'login failure' });
    // };
});

app.use('/authenticated', isAuthenticated, router)

app.listen(process.env.PORT || 3000, () => {
    console.log(`listening on port ${process.env.PORT || 3000}`);
});

