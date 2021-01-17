//Aby uruchomić autmoatyczne kompilowanie przy zapisie: npm start
//Aby skompilować z opcjami optymalizacji: npm run build
//Ustawienia
const SETTINGS = {
    entry: {
        app: "./assets/js/app.js"
    },
    presets: [/*'@babel/preset-react',*/ '@babel/preset-env'],
    jsOutput: 'js/',
    cssOutput: 'css/'
}


const path = require("path");
const webpack = require("webpack");
const MiniCssExtractPlugin = require("mini-css-extract-plugin");
//const CompressionPlugin = require("compression-webpack-plugin");
const TerserPlugin = require('terser-webpack-plugin');
const OptimizeCSSAssetsPlugin = require("optimize-css-assets-webpack-plugin");

process.traceDeprecation = true;

module.exports  = (env, argv) => {
    var minimizer = (argv.mode === 'production') ? [
       new TerserPlugin({
            parallel: true,
            terserOptions: {
              ecma: 6,
            },
        }),
        new OptimizeCSSAssetsPlugin({
            cssProcessorOptions: {
                safe: true,
                discardComments: {
                    removeAll: true,
                },
            },
        })
    ]:[];
    return {
        entry: SETTINGS.entry,
        output: {
            path: __dirname,
            filename: SETTINGS.jsOutput+"[name].min.js",
            publicPath: "/",
            pathinfo: false
        },
        optimization: {
            minimizer: [
                ...minimizer
            ]
        },
        plugins: [
            new webpack.ContextReplacementPlugin(/\.\/locale$/, 'empty-module', false, /jsx$/),
            new webpack.LoaderOptionsPlugin({
                options: {}
            }),
            new MiniCssExtractPlugin({
                filename: SETTINGS.cssOutput+"[name].css",
                chunkFilename: SETTINGS.cssOutput+"[id].css"
            }),
            /*new webpack.ProvidePlugin({
                $: "jquery",
                jQuery: "jquery",
                Popper: ['popper.js', 'default']
            }),*/
            /*new CompressionPlugin({
                test: /\.(js|css)/
            }),*/
        ],
        module: {
            rules: [{
                    test: /\.scss$/,
                    use: [
                        'style-loader',
                        MiniCssExtractPlugin.loader,
                        {
                            loader: "css-loader",
                        },
                        {
                            loader: 'postcss-loader',
                            options: {
                                postcssOptions: {
                                    plugins: [
                                      [
                                        'autoprefixer',
                                        {
                                          overrideBrowserslist: ['defaults', 'ie 11']
                                        },
                                      ],
                                    ],
                                }
                            }
                        },
                        {
                            loader: "sass-loader"
                        }
                    ]
                },
                {

                    test: /\.(js|jsx)$/,
                    exclude: /node_modules/,
                    use: {
                        loader: 'babel-loader',
                        options: {
                            presets: SETTINGS.presets
                        }
                    }
                },
                {
                    test: /\.(jpe?g|png|gif)$/i,
                    loader: "file-loader"
                },
                {
                    test: /\.(woff|ttf|otf|eot|woff2|svg)$/i,
                    loader: "file-loader"
                }
            ]
        }
    }
};