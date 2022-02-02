package com.example.directorytraversalcpp

import android.os.Bundle
import android.util.Log
import android.view.View
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.example.directorytraversalcpp.databinding.ActivityMainBinding

private const val TAG = "MainActivity"

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    private lateinit var recyclerViewAdapter: RecyclerViewAdapter

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        val currentPath : String? = getCurrentPath()
        currentPath?.let {
            path ->
            binding.directoryPathText.text = path
            val fileList : Array<String>? = getPathList(currentPath)
            fileList?.let {
                recyclerViewAdapter = RecyclerViewAdapter(this)
                recyclerViewAdapter.replaceList(fileList.toCollection(ArrayList()))
                recyclerViewAdapter.setOnItemClickListener(object :
                    RecyclerViewAdapter.OnItemClickListener {
                    override fun onItemClick(v: View, data: String, pos: Int) {
                        traversalDir(data)
                    }
                })
                binding.directoryItemRecyclerView.adapter = recyclerViewAdapter
            }
        }
    }

    private fun traversalDir(p: String) {
        val hashMap: HashMap<String, String>? = getFileInfo(p)
        hashMap?.let{
            when (it["type"]) {
                "file" -> Toast.makeText(applicationContext, "Not A Dir", Toast.LENGTH_SHORT).show()
                "directory" -> {
                    val origPath : String = getCurrentPath()

                    val changedPath: String = getPath(p)
                    if (changedPath.isEmpty()) {
                        Toast.makeText(applicationContext, "permission denied! Can't get Path!", Toast.LENGTH_SHORT).show()
                    } else {
                        Log.e(TAG, "onItemClick: $changedPath")
                        var fileList : Array<String>? = getPathList(changedPath)
                        fileList?.let {
                            d ->
                            binding.directoryPathText.text = changedPath
                            recyclerViewAdapter.replaceList(d.toCollection(ArrayList()))
                        } ?: run{
                            getPath(origPath)
                            Toast.makeText(this,"permission denied! Can't get Path List!", Toast.LENGTH_SHORT).show()
                        }
                    }
                }
            }
        } ?: run{
            Toast.makeText(this, "permission denied! Can't get File Info!", Toast.LENGTH_SHORT).show()
        }
    }

    override fun onBackPressed() {
        if (getCurrentPath() == "/") super.onBackPressed() else traversalDir("..")
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    external fun getCurrentPath(): String

    external fun getPath(path: String): String

    external fun getPathList(path: String): Array<String>

    external fun getFileInfo(path: String): HashMap<String, String>

    companion object {
        init {
            System.loadLibrary("native-lib")
        }
    }
}
