import { useEffect, useState } from 'react';
import axios from 'axios';
import { Flex } from '@chakra-ui/react'
const Authenticated = (): JSX.Element => {

    const [message, setMessage] = useState('You are not authenticated.');

    useEffect(() => {
        const fetchData = async () => {
            const authToken = localStorage.getItem('jwt');
            const response = await axios.get('http://localhost:3000/authenticated', {
                headers: {
                    'Authorization': `Bearer ${authToken}`,
                    'Content-Type': 'application/json'
                }
            });
            setMessage(response.data.message);
        };
        fetchData();
    }, [])

    return <Flex justify='center' align='center'>
        {message}
    </Flex>
}

export default Authenticated;