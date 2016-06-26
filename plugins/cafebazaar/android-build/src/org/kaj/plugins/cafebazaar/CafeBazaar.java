package org.kaj.plugins.cafebazaar;

import org.kaj.KajActivity;
import org.kaj.util.iap.*;

import android.util.Log;



class CafeBazaar{
	private static String TAG = "BazaarManager";
	private static IabHelper mHelper;
	private static String SKU_PREMIUM = "premium";
	private static final int RC_REQUEST = 1;

	public native static void purchaseFinished(boolean isSuccessfull, String name);

	public CafeBazaar(){
		mHelper.startSetup(new IabHelper.OnIabSetupFinishedListener() {

			@Override
			public void onIabSetupFinished(IabResult result) {
				Log.d(TAG , "Setup finished.");

				if (!result.isSuccess()) {
					// Oh noes, there was a problem.
					Log.d(TAG, "Problem setting up In-app Billing: " + result);
				}
				// Hooray, IAB is fully set up!
				mHelper.queryInventoryAsync(mGotInventoryListener);
			}

		});
	}

	public static void Purchase(String name, String publicKey){
		final String skuName = name;

		mHelper = new IabHelper(KajActivity.getInstance(), publicKey);
		
		try{
			mHelper.startSetup(new IabHelper.OnIabSetupFinishedListener() {

				@Override
				public void onIabSetupFinished(IabResult result) {
					Log.d(TAG , "Setup finished.");

					if (!result.isSuccess()) {
						// Oh noes, there was a problem.
						Log.d(TAG, "Problem setting up In-app Billing: " + result);
					}
					// Hooray, IAB is fully set up!
					mHelper.launchPurchaseFlow(KajActivity.getInstance(), 
							skuName, 
							RC_REQUEST, 
							mPurchaseFinishedListener, 
							"payload-string");
				}

			});
		} catch(Exception ex){
			ex.printStackTrace();
		}


	}

	IabHelper.QueryInventoryFinishedListener mGotInventoryListener = new IabHelper.QueryInventoryFinishedListener() {
		@Override
		public void onQueryInventoryFinished(IabResult result, Inventory inventory) {
			Log.d(TAG, "Query inventory finished.");
			if (result.isFailure()) {
				Log.d(TAG, "Failed to query inventory: " + result);
				return;
			}
			else {
				Log.d(TAG, "Query inventory was successful.");
				// does the user have the premium upgrade?
				boolean mIsPremium = inventory.hasPurchase(SKU_PREMIUM);

				// update UI accordingly

				Log.d(TAG, "User is " + (mIsPremium ? "PREMIUM" : "NOT PREMIUM"));
			}

			Log.d(TAG, "Initial inventory query finished; enabling main UI.");
		}
	};

	static IabHelper.OnIabPurchaseFinishedListener mPurchaseFinishedListener = new IabHelper.OnIabPurchaseFinishedListener() {

		@Override
		public void onIabPurchaseFinished(IabResult result, Purchase purchase) {
			if (result.isFailure()) {
				Log.d(TAG, "Error purchasing: " + result);
				purchaseFinished(false, "");
				return;
			}
			else if (purchase.getSku().equals(SKU_PREMIUM)) {
				purchaseFinished(true, purchase.getSku());
				// give user access to premium content and update the UI
			}
		}
	};
}