# Pandas is used for data manipulation
import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
# Import the model we are using
from sklearn.ensemble import RandomForestRegressor
from pprint import pprint
from sklearn.model_selection import RandomizedSearchCV
from sklearn.model_selection import GridSearchCV

# import seaborn as sns
import time


def main():
  loop_amount = 1
  temp_acc = 0
  max_acc = 0
  for i in range(loop_amount):
    temp_acc = run_model()
    if (temp_acc > max_acc):
      max_acc = temp_acc

  print("\nBest Accuracy found: ", max_acc)

def run_model():
  start_time = time.time()
  print("\n\n\nSTART", end='\n', flush=True)
  
  # Read in data and display first 5 rows
  #----------------------------------------------------------------
  print(" - CSV File Read... ", end="", flush=True)
  features = pd.read_csv('V4.csv')
  print(
    "                                           Successfully",
    flush=True)
  #----------------------------------------------------------------
  
  # One-hot encode the data using pandas get_dummies
  print(" - One Hot Values Assigned... ", end="", flush=True)
  features = pd.get_dummies(features)
  print("                                 Successfully", flush=True)
  #----------------------------------------------------------------
  
  # Labels are the values we want to predict
  print(" - Isolated the Labels... ", end="", flush=True)
  labels = np.array(features['Critic_Score'])
  print("                                     Successfully",
        flush=True)
  #----------------------------------------------------------------
  
  # Remove the labels from the features
  print(" - Dropping Prediction Target Axis... ", end="", flush=True)
  features = features.drop('Critic_Score', axis=1)
  print("                         Successfully", flush=True)
  #----------------------------------------------------------------
  
  # Saving feature names for later use
  print(" - Saving Feature Names... ", end="", flush=True)
  feature_list = list(features.columns)
  print("                                    Successfully", flush=True)
  #----------------------------------------------------------------
  
  # Convert to numpy array
  print(" - Converting Numpy Array... ", end="", flush=True)
  features = np.array(features)
  print("                                  Successfully", flush=True)
  #----------------------------------------------------------------
  
  # Split the data into training and testing sets
  print(" - Splitting Data Into Training and Testing Sets... ",
        end="",
        flush=True)
  train_features, test_features, train_labels, test_labels = train_test_split(
    features, labels, test_size=0.2, random_state=42)
  print("           Successfully", flush=True)
  #----------------------------------------------------------------
  
  #build random forest
  
  print(" - Building Random Forest... ", end="", flush=True)
  rf = RandomForestRegressor(bootstrap=True
 )
  
  
  print("                                  Successfully", flush=True)
  #----------------------------------------------------------------
  
  # Train the model on training data
  print(" - Training Model on Training Data... ", end="", flush=True)
  rf.fit(train_features, train_labels)
  print("                         Successfully", flush=True)
  #----------------------------------------------------------------
  
  # # Use the forest's predict method on the test data
  print(" - Predicting Values With Random Forest... ", end="", flush=True)
  predictions = rf.predict(test_features)
  print("                    Successfully", flush=True)
  #----------------------------------------------------------------
  
  
  # Calculate the absolute errors
  errors = abs(predictions - test_labels)
  mape = 100 * (errors / test_labels)
  print(" - Calculating Accuracy... ", end="", flush=True)
  accuracy = 100 - np.mean(mape)
  print("                                    Successfully",
        end="\n",
        flush=True)
  #----------------------------------------------------------------
  
  # Get numerical feature importances
  print(" - Calculating Feature Importances... ", end="", flush=True)
  importances = list(rf.feature_importances_)
  print("                         Successfully", end="\n", flush=True)
  #----------------------------------------------------------------
  
  # List of tuples with variable and importance
  print(" - Calculating Importance of Variables...", end="", flush=True)
  feature_importances = [
    (feature, round(importance, 8))
    for feature, importance in zip(feature_list, importances)
  ]
  print("                      Successfully", end="\n", flush=True)
  #----------------------------------------------------------------
  
  # Sort the feature importances by most important first
  print(" - Sorting Importance of Features...", end="", flush=True)
  feature_importances = sorted(feature_importances,
                               key=lambda x: x[1],
                               reverse=True)
  print("                           Successfully")
  #----------------------------------------------------------------
  
  # Print out the feature and importances
  print(" - Printing Importance to Output File... ", end="", flush=True)
  with open('output.txt', 'w') as f:
    [
      print('Variable: {:20} Importance: {}'.format(*pair), file=f)
      for pair in feature_importances
    ]
  print("                      Successfully")
  #----------------------------------------------------------------
  
  print("END")
  
  print('\nThe shape of our features is:', features.shape)
  print('Training Features Shape:', train_features.shape)
  print('Training Labels Shape:', train_labels.shape)
  print('Testing Features Shape:', test_features.shape)
  print('Testing Labels Shape:', test_labels.shape)
  
  
  f = open('predictions.csv', 'w')
  
  index = 0
  
  while (index < len(predictions)):
    f.write(str(predictions[index]) + "," + str(test_labels[index]) + "\n")
    index += 1
  
  f.close()
  
  
  # Look at parameters used by our current forest
  print('Parameters currently in use:')
  pprint(rf.get_params())
  print("\n")

  print('\nAccuracy:', abs(accuracy), '%.', '\n')
  print("--- Runtime %s seconds ---" % (time.time() - start_time))
  return abs(accuracy)

def evaluate(model, test_features, test_labels):
    predictions = model.predict(test_features)
    errors = abs(predictions - test_labels)
    mape = 100 * np.mean(errors / test_labels)
    accuracy = 100 - mape
    print('Model Performance')
    print('Average Error: {:0.4f} degrees.'.format(np.mean(errors)))
    print('Accuracy = {:0.2f}%.'.format(accuracy))

main()

#grid search params (use after rf is built)
 #  {'bootstrap': True,
 # 'ccp_alpha': 0.0,
 # 'criterion': 'squared_error',
 # 'max_depth': 110,
 # 'max_features': 3,
 # 'max_leaf_nodes': None,
 # 'max_samples': None,
 # 'min_impurity_decrease': 0.0,
 # 'min_samples_leaf': 3,
 # 'min_samples_split': 10,
 # 'min_weight_fraction_leaf': 0.0,
 # 'n_estimators': 300,
 # 'n_jobs': None,
 # 'oob_score': False,
 # 'random_state': None,
 # 'verbose': 0,
 # 'warm_start': False}
  # # Number of trees in random forest
  # n_estimators = [int(x) for x in np.linspace(start = 200, stop = 2000, num = 10)]
  # # Number of features to consider at every split
  # max_features = ['auto', 'sqrt']
  # # Maximum number of levels in tree
  # max_depth = [int(x) for x in np.linspace(10, 100, num = 10)]
  # max_depth.append(None)
  # # Minimum number of samples required to split a node
  # min_samples_split = [2, 5, 10]
  # # Minimum number of samples required at each leaf node
  # min_samples_leaf = [1, 2, 4]
  # # Method of selecting samples for training each tree
  # bootstrap = [True, False]
  
  # # Create the random grid
  # random_grid = {'n_estimators': n_estimators,
  #                'max_features': max_features,
  #                'max_depth': max_depth,
  #                'min_samples_split': min_samples_split,
  #                'min_samples_leaf': min_samples_leaf,
  #                'bootstrap': bootstrap}
  
  # # Use the random grid to search for best hyperparameters
  # # First create the base model to tune
  # rf = RandomForestRegressor()
  # # Random search of parameters, using 3 fold cross validation, 
  # # search across 100 different combinations, and use all available cores
  # rf_random = RandomizedSearchCV(estimator=rf, param_distributions=random_grid,
  #                               n_iter = 100, scoring='neg_mean_absolute_error', 
  #                               cv = 3, verbose=2, random_state=42, n_jobs=-1)
  
  # # Fit the random search model
  # rf_random.fit(train_features, train_labels)
  # base_model = RandomForestRegressor(n_estimators = 1000, random_state = 42)
  # base_model.fit(train_features, train_labels)
  # evaluate(base_model, test_features, test_labels)

  # best_random = rf_random.best_estimator_
  # evaluate(best_random, test_features, test_labels)

  # Create the parameter grid based on the results of random search 
  # param_grid = {
  #     'bootstrap': [True],
  #     'max_depth': [80, 90, 100, 110],
  #     'max_features': [2, 3],
  #     'min_samples_leaf': [3, 4, 5],
  #     'min_samples_split': [8, 10, 12],
  #     'n_estimators': [100, 200, 300, 1000]
  # }
  
  # # Create a based model
  # rf = RandomForestRegressor()
  
  # # Instantiate the grid search model
  # grid_search = GridSearchCV(estimator = rf, param_grid = param_grid, 
  #                            scoring = 'neg_mean_absolute_error', cv = 3, 
  #                            n_jobs = -1, verbose = 2)

  # # Fit the grid search to the data
  # grid_search.fit(train_features, train_labels)
  # best_grid = grid_search.best_estimator_
  # evaluate(best_grid, test_features, test_labels)

  # print('Model Parameters:\n')
  # pprint(best_grid.get_params())
  # print('\n')
  # evaluate(best_grid, test_features, test_labels)