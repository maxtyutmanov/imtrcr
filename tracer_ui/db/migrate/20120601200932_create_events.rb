class CreateEvents < ActiveRecord::Migration
  def change
    create_table :events do |t|
      t.datetime :time
      t.text :description

      t.timestamps
    end
  end
end
