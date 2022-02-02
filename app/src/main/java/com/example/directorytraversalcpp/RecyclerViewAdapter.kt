package com.example.directorytraversalcpp

import android.content.Context
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView

class RecyclerViewAdapter (private val context: Context) : RecyclerView.Adapter<RecyclerViewAdapter.ViewHolder>() {

    var fileData = arrayListOf<String>()

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        val view = LayoutInflater.from(context).inflate(R.layout.directory_file_list, parent ,false)
        return ViewHolder(view)
    }

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        holder.bind(fileData[position])
    }

    override fun getItemCount(): Int = fileData.size

    fun replaceList(list : ArrayList<String>){
        fileData = list

        notifyDataSetChanged()
    }

    inner class ViewHolder(view: View) : RecyclerView.ViewHolder(view) {

        private val pathName: TextView = itemView.findViewById(R.id.file_name)

        fun bind(item: String) {
            pathName.text = item

            val pos = adapterPosition
            if(pos!= RecyclerView.NO_POSITION)
            {
                itemView.setOnClickListener {
                    listener?.onItemClick(itemView, item, pos)
                }
            }
        }
    }

    interface OnItemClickListener{
        fun onItemClick(v:View, data: String, pos : Int)
    }

    private var listener : OnItemClickListener? = null

    fun setOnItemClickListener(listener : OnItemClickListener) {
        this.listener = listener
    }
}