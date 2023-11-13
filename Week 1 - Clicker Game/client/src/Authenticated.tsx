import { useEffect, useState } from 'react';
import axios from 'axios';
import { Spinner } from '@chakra-ui/react'
const Authenticated = (): JSX.Element => {

    const [message, setMessage] = useState(null);

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

    return message ? <div>{message}</div> : <Spinner />
}

export default Authenticated;