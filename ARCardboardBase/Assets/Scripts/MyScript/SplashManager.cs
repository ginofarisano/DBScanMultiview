using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class SplashManager : MonoBehaviour
{
	#region MONOBEHAVIOUR_METHODS
	void Start()
	{
		StartCoroutine(LoadNextSceneAfter(5));
	}
	#endregion // MONOBEHAVIOUR_METHODS

	#region PRIVATE_METHODS
	private IEnumerator LoadNextSceneAfter(float seconds)
	{
		yield return new WaitForSeconds(seconds);
		
		Application.LoadLevel(Application.loadedLevel+1);

	}
	#endregion // PRIVATE_METHODS
}