import dotenv from 'dotenv';
import express, { NextFunction, Request, Response } from 'express';
import { router } from './router';
import jwt from 'jsonwebtoken';
dotenv.config();

const app = express();
app.use(express.json());

const isAuthenticated = (req: Request, res: Response, next: NextFunction) => {
    const token = req.headers.authorization?.split(' ')[1];

    try {
        if (!token) return res.status(401).json({ message: 'no jwt token provided' });
        jwt.verify(token, process.env.SECRET_KEY as string, (err, decoded) => {
            if (err) throw err;
        });
        next();
    } catch (err) {
        next(err);
        return res.status(401).json({ message: "you are not authenticated" });
    }
};

app.post('/login', (req: Request, res: Response) => {
    const username = req.body.username;
    const password = req.body.password;

    // TODO: implement storing username + password hash on mongoDB with bcrypt
    // verify user credentials
    // for now: only valid credentials are {username: user, password: pass}

    if (username === 'user' && password === 'pass') {
        var token = jwt.sign({ username }, process.env.SECRET_KEY as string, {
            // 1 hour
            expiresIn: 60 * 60
        });
        res.cookie("jwt", token);
        res.status(200).json({ message: 'login success' });
    } else {
        res.status(401).json({ message: 'login failure' });
    }
});

app.use('/api', router)
app.get('/auth', isAuthenticated, (req: Request, res: Response, next) => {
    res.json('this is authorized route');
});

app.listen(process.env.PORT || 3000, () => {
    console.log(`listening on port ${process.env.PORT || 3000}`);
});

