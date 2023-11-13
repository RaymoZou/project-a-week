import { Flex, FormControl, FormLabel, Input, Button, Heading } from "@chakra-ui/react";
import { useState } from 'react';
import axios from 'axios';

const Signup = () => {

    const [formData, setFormData] = useState({
        username: '',
        password: ''
    });

    const submitForm = async (e: React.MouseEvent<HTMLButtonElement>) => {
        e.preventDefault();
        // TODO: replace hard-coded URL with .env variable
        try {
            const res = await axios.post('http://localhost:3000/signup', formData);
            console.log(res);
        } catch (err) {
            console.log(err);
        }
    };

    const handleInputChange = (e: React.ChangeEvent<HTMLInputElement>) => {
        const value : string = e.target.value;
        const name : string = e.target.name;
        setFormData((prevData) => ({
            ...prevData,
            [name]: value,
        }));
    }

    return <Flex h='100vh' justify='center' align='center' direction='column' gap={8}>
        <Heading>Sign Up</Heading>
        <form action="">
            <FormControl w='max-content'>
                <FormLabel>Username</FormLabel>
                <Input
                    type='email'
                    name='username'
                    autoComplete='username'
                    value={formData.username}
                    onChange={handleInputChange} />
            </FormControl>
            <FormControl w='max-content'>
                <FormLabel>Password</FormLabel>
                <Input
                    type='password'
                    name='password'
                    autoComplete='current-password'
                    value={formData.password}
                    onChange={handleInputChange} />
            </FormControl>
            <Button onClick={submitForm}>Submit</Button>
        </form>
    </Flex>
}

export default Signup;