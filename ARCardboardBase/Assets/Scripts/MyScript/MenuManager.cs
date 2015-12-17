using UnityEngine;
using System.Collections;

public class MenuManager : MonoBehaviour
{
	#region PUBLIC_METHODS
	public void OnStartAR()
	{
		Application.LoadLevel("AR");
	}
	#endregion // PUBLIC_METHODS
	
	
	#region MONOBEHAVIOUR_METHODS
	void Update()
	{
		#if UNITY_ANDROID
		// On Android, the Back button is mapped to the Esc key
		if (Input.GetKeyUp(KeyCode.Escape))
		{
			// Exit app
			Application.Quit();
		}
		#endif
	}
	#endregion // MONOBEHAVIOUR_METHODS
}