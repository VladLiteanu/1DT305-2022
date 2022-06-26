import React, { useEffect, useState } from 'react';
import './home.css';
import Chart from '../components/BarChart';
import { render } from 'react-dom';
import { Api } from '../axios';
import Grid from '@material-ui/core/Grid';
import Typography from '@mui/material/Typography';
import Breadcrumbs from '@mui/material/Breadcrumbs';
import Link from '@mui/material/Link';
import HomeIcon from '@mui/icons-material/Home';
import InfoIcon from '@mui/icons-material/Info';

class Home extends React.Component {
    constructor(props) {
        super();
        this.state = {
            chartData: props.chartData
        }
    }

    componentWillMount() {
        this.getChartData();
    }


    handleClick(event) {
        console.info('You clicked a breadcrumb.');
    }

    getChartData() {
        var analogTemp = [];
        var dhtTemp = [];
        var dhtHumidity = [];
        var heatIndex = [];
        var light = [];
        var motion = [];
        var sound = [];
        var steam = [];
        var time = [];

        // Ajax call to get data from server
        Api.get('/api/sensorDatas').then(response => {
            console.log(response.data);
            response.data.sensorData.forEach(element => {
                analogTemp.push(element.analogTemp);
                var date = new Date(element.time);
                time.push(date.toLocaleString());
                dhtTemp.push(element.dhtTemp);
                dhtHumidity.push(element.humidity);
                heatIndex.push(element.heatIndex);
                light.push(element.light);
                motion.push(element.motion);
                sound.push(element.sound);
                steam.push(element.steam);
            });
            this.setState({});
        }).catch(error => {
            console.log(error);
            alert("Error getting data from server");
        });

        this.setState({
            analogTempData: {
                labels: time,
                datasets: [
                    {
                        label: 'Analog temperature',
                        data: analogTemp,
                        backgroundColor: 'rgba(168, 218, 220, 1)',
                        borderColor: 'rgba(230, 57, 70, 1)',
                    }
                ]
            },
            dhtTempData: {
                labels: time,
                datasets: [
                    {
                        label: 'DHT temperature',
                        data: dhtTemp,
                        backgroundColor: 'rgba(168, 218, 220, 1)',
                        borderColor: 'rgba(230, 57, 70, 1)',
                    }
                ]
            },
            dhtHumData: {
                labels: time,
                datasets: [
                    {
                        label: 'DHT humidity',
                        data: dhtHumidity,
                        backgroundColor: 'rgba(168, 218, 220, 1)',
                        borderColor: 'rgba(230, 57, 70, 1)',

                    }
                ]
            },
            heatIndexData: {
                labels: time,
                datasets: [
                    {
                        label: 'Heat index',
                        data: heatIndex,
                        backgroundColor: 'rgba(168, 218, 220, 1)',
                        borderColor: 'rgba(230, 57, 70, 1)',
                    }
                ]
            },
            lightData: {
                labels: time,
                datasets: [
                    {
                        label: 'Light',
                        data: light,
                        backgroundColor: 'rgba(168, 218, 220, 1)',
                        borderColor: 'rgba(230, 57, 70, 1)',
                    }
                ]
            },
            motionData: {
                labels: time,
                datasets: [
                    {
                        label: 'Motion',
                        data: motion,
                        backgroundColor: 'rgba(168, 218, 220, 1)',
                        borderColor: 'rgba(230, 57, 70, 1)',
                    }
                ]
            },
            soundData: {
                labels: time,
                datasets: [
                    {
                        label: 'Sound',
                        data: sound,
                        backgroundColor: 'rgba(168, 218, 220, 1)',
                        borderColor: 'rgba(230, 57, 70, 1)',
                    }
                ]
            },
            steamData: {
                labels: time,
                datasets: [
                    {
                        label: 'Steam',
                        data: steam,
                        backgroundColor: 'rgba(168, 218, 220, 1)',
                        borderColor: 'rgba(230, 57, 70, 1)',
                    }
                ]
            },
        })
    }

    render() {
        return (
            <>
                <Grid container spacing={1}>
                    <Grid item xs={12}>
                        <div role="presentation" onClick={this.handleClick}>
                            <Breadcrumbs aria-label="breadcrumb">
                                <Link
                                    underline="hover"
                                    sx={{ display: 'flex', alignItems: 'center' }}
                                    color="#1D3557"
                                    href="/about">
                                    <InfoIcon sx={{ mr: 0.5 }} fontSize="inherit" />
                                    About
                                </Link>
                                <Typography sx={{ display: 'flex', alignItems: 'center' }}
                                    color="text.primary">
                                    <HomeIcon sx={{ mr: 0.5 }} fontSize="inherit" />
                                    Home
                                </Typography>
                            </Breadcrumbs>
                        </div>
                    </Grid>

                    <Grid item xs={6}>
                        <div className='chart'>
                            <Chart chartData={this.state.analogTempData} titleText={"Analog temperature"} />
                        </div>
                    </Grid>
                    <Grid item xs={6}>
                        <div className='chart'>
                            <Chart chartData={this.state.dhtTempData} titleText={"DHT temperature"} />
                        </div>
                    </Grid>
                    <Grid item xs={6}>
                        <div className='chart' >
                            <Chart chartData={this.state.dhtHumData} titleText={"DHT humidity"} />
                        </div>
                    </Grid>
                    <Grid item xs={6}>
                        <div className='chart' >
                            <Chart chartData={this.state.heatIndexData} titleText={"Heat index"} />
                        </div>
                    </Grid>
                    <Grid item xs={6}>
                        <div className='chart' >
                            <Chart chartData={this.state.lightData} titleText={"Light data"} />
                        </div>
                    </Grid>
                    <Grid item xs={6}>
                        <div className='chart' >
                            <Chart chartData={this.state.motionData} titleText={"Motion data"} />
                        </div>
                    </Grid>
                    <Grid item xs={6}>
                        <div className='chart' >
                            <Chart chartData={this.state.soundData} titleText={"Sound data"} />
                        </div>
                    </Grid>
                    <Grid item xs={6}>
                        <div className='chart' >
                            <Chart chartData={this.state.steamData} titleText={"Steam data"} />
                        </div>
                    </Grid>
                </Grid>
            </>
        );
    }
}

export default Home;