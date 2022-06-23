import React, { useEffect, useState } from 'react';
import './index.css';
import Chart from '../components/BarChart';
import { render } from 'react-dom';
import { Api } from '../axios';

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
        });

        this.setState({
            analogTempData: {
                labels: time,
                datasets: [
                    {
                        label: 'Analog temperature',
                        data: analogTemp,
                        backgroundColor: 'rgba(255, 99, 132, 1)',
                    }
                ]
            },
            dhtTempData: {
                labels: time,
                datasets: [
                    {
                        label: 'DHT temperature',
                        data: dhtTemp,
                        backgroundColor: 'rgba(255, 99, 132, 1)',
                    }
                ]
            },
            dhtHumData: {
                labels: time,
                datasets: [
                    {
                        label: 'DHT humidity',
                        data: dhtHumidity,
                        backgroundColor: 'rgba(255, 99, 132, 1)',

                    }
                ]
            },
            heatIndexData: {
                labels: time,
                datasets: [
                    {
                        label: 'Heat index',
                        data: heatIndex,
                        backgroundColor: 'rgba(255, 99, 132, 1)',
                    }
                ]
            },
            lightData: {
                labels: time,
                datasets: [
                    {
                        label: 'Light',
                        data: light,
                        backgroundColor: 'rgba(255, 99, 132, 1)',
                    }
                ]
            },
            motionData: {
                labels: time,
                datasets: [
                    {
                        label: 'Motion',
                        data: motion,
                        backgroundColor: 'rgba(255, 99, 132, 1)',
                    }
                ]
            },
            soundData: {
                labels: time,
                datasets: [
                    {
                        label: 'Sound',
                        data: sound,
                        backgroundColor: 'rgba(255, 99, 132, 1)',
                    }
                ]
            },
            steamData: {
                labels: time,
                datasets: [
                    {
                        label: 'Steam',
                        data: steam,
                        backgroundColor: 'rgba(255, 99, 132, 1)',
                    }
                ]
            },
        })
    }

    render() {
        return (
            <>
                <div style={{ backgroundColor: '#d8dae3', marginBottom: '5px' }}>
                    <Chart chartData={this.state.analogTempData} titleText={"Analog temperature"} />
                </div>
                <div style={{ backgroundColor: '#d8dae3', marginBottom: '5px' }}>
                    <Chart chartData={this.state.dhtTempData} titleText={"DHT temperature"} />
                </div>
                <div style={{ backgroundColor: '#d8dae3', marginBottom: '5px' }}>
                    <Chart chartData={this.state.dhtHumData} titleText={"DHT humidity"} />
                </div>
                <div style={{ backgroundColor: '#d8dae3', marginBottom: '5px' }}>
                    <Chart chartData={this.state.heatIndexData} titleText={"Heat index"} />
                </div>
                <div style={{ backgroundColor: '#d8dae3', marginBottom: '5px' }}>
                    <Chart chartData={this.state.lightData} titleText={"Light data"} />
                </div>
                <div style={{ backgroundColor: '#d8dae3', marginBottom: '5px' }}>
                    <Chart chartData={this.state.motionData} titleText={"Motion data"} />
                </div>
                <div style={{ backgroundColor: '#d8dae3', marginBottom: '5px' }}>
                    <Chart chartData={this.state.soundData} titleText={"Sound data"} />
                </div>
                <div style={{ backgroundColor: '#d8dae3', marginBottom: '5px' }}>
                    <Chart chartData={this.state.steamData} titleText={"Steam data"} />
                </div>
            </>
        );
    }
}

export default Home;