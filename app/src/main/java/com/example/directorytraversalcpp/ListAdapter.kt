package com.example.directorytraversalcpp

import android.content.Context
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.BaseAdapter
import android.widget.TextView

class ListAdapter(val context: Context, val fileList: ArrayList<String>) : BaseAdapter() {
    override fun getCount(): Int {
        return fileList.size
    }

    override fun getItem(position: Int): Any {
        return fileList[position]
    }

    override fun getItemId(position: Int): Long {
        return 0
    }

    override fun getView(position: Int, convertView: View?, parent: ViewGroup?): View {
        val view: View = LayoutInflater.from(context).inflate(R.layout.directory_file_list, null)

        val fileName = view.findViewById<TextView>(R.id.file_name)
        val file = fileList[position]
        fileName.text = file

        return view
    }
}