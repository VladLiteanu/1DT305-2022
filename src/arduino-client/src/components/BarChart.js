import React from "react";
import { Line } from "react-chartjs-2";
import { Chart as ChartJS } from 'chart.js/auto';
import { render } from "react-dom";


class Chart extends React.Component {
    constructor(props) {
        super(props);
        this.state = {
            chartData: props.chartData
        }
    }

    static defaultProps = {
        displayTitle: true,
        displayLegend: false,
        legendPosition: 'bottom',
        titleText: 'Chart',
    }

    render() {
        return (
            <div className="chart">
                <Line
                    data={this.state.chartData}
                    width={400}
                    height={600}
                    options={{
                        maintainAspectRatio: false,
                        plugins: {
                            title: {
                                display: this.props.displayTitle,
                                text: this.props.titleText,
                            },
                            legend: {
                                display: this.props.displayLegend,
                                position: this.props.legendPosition
                            },
                        },
                        scales: {
                            y: {
                                beginAtZero: true,
                                ticks: {
                                    font: {
                                        size: 14,
                                    }
                                }
                            },
                            x: {
                                ticks: {
                                    font: {
                                        size: 10,
                                    }
                                }
                            }
                        },

                    }}
                />
            </div>
        )
    }
}

export default Chart;