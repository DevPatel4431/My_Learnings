# 📈 Uber Stock Price Prediction using KNN Regression

This project predicts **Uber stock prices** using a **K-Nearest Neighbors (KNN) Regression model**.  
The dataset is preprocessed, analyzed, visualized, and modeled to evaluate how well KNN can predict trading volume and price relations.

---

## 🧠 Project Overview

- 📊 Dataset: `uber_stock_data-Copy.csv`  
- 🔍 Model: **KNN Regressor** from `scikit-learn`
- ⚙️ Distance Metric: **Manhattan (p=2)**  
- 🎯 Goal: Predict the **Volume** of trades using stock features (`Adj Close`, `Close`, `High`, `Low`, `Open`)  

---

## 🧩 Features Used

| Feature | Description |
|----------|--------------|
| `Adj Close` | Adjusted closing price |
| `Close` | Closing price |
| `High` | Highest price of the day |
| `Low` | Lowest price of the day |
| `Open` | Opening price |
| `Volume` | Trading volume (target variable) |

---

## 📦 Dependencies

Install the following Python libraries before running the project:

```bash
pip install pandas numpy matplotlib scikit-learn
```

---

## 🧮 Results

| Metric       | Value  |
| ------------ | ------ |
| **MSE**      | 6.0647 |
| **R² Score** | 0.1004 |
| **MAE**      | 1.6109 |
| **RMSE**     | 2.4627 |
| **MAPE**     | 6.48%  |

---

## 📊 Sample Output
```
Test MSE with k=4 and Manhattan distance: 6.0647
R2 Score: 0.1004
Mean Absolute Error: 1.6109
Root Mean Squared Error: 2.4627
Current Model MAPE: 6.48%
```

---

## 🧠 Insights

The R² score suggests the model captures limited variance, likely due to linear trends in the data.
KNN performs reasonably with normalized data, but tuning `k` and scaling features can improve results.
MAPE ~6.5% indicates the predictions are fairly close to actual trading volumes.

---

## 👨‍💻 Author

**Dev Patel**  
🌐 [github.com/DevPatel4431](https://github.com/DevPatel4431)

