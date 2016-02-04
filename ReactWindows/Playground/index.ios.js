'use strict';

const React = require('react-native');
const styles={
   views:{
       flexDirection: 'column'
   },
   images: {
       height:200,
       width:250,
       borderWidth: 5,
       marginTop: 6,
       borderColor: '#015d87',
       borderRadius: 10
   },
   textInput: {
       height: 40,
       borderWidth: 5, 
       borderColor: '#015d87'
   },
   longTextInput: {
       height: 80,
       borderWidth: 3,
       borderColor: '#ccc'
   }
};

var {AppRegistry, View, Text, TextInput, Image } = React;

    var ReactRoot = React.createClass({
		
	getInitialState: function(){
		var text = "You can see me!";
        var longText = "This is such a long text that it needs to go into a new lineThis is such a long text that it needs to go into a new lineThis is such a long text that it needs to go into a new lineThis is such a long text that it needs to go into a new lineThis is such a long text that it needs to go into a new line";
        
		return {value: text,
                longText: longText};
	},

    render: function() {
        let imageURL = "http://image.slidesharecdn.com/tel-aviv-meetup-150809210316-lva1-app6892/95/pieter-de-baets-an-introduction-to-react-native-1-638.jpg?cb=1439154582";
        
        return (
            <View>
              <View style={styles.views}>
		         <Text>Hello World!</Text>
				{(this.state && this.state.value) 
			     ? <TextInput value={this.state.value} style={styles.textInput}></TextInput> 
				 : undefined}
                
                {(this.state && this.state.longText) 
			     ? <TextInput value={this.state.longText} multiline={true} style={styles.longTextInput}></TextInput> 
				 : undefined}
              </View>
              <View style={styles.views}>
                 <Image source={{uri: imageURL}} style={styles.images}/>
              </View>
            </View>
        );
    }
 });

AppRegistry.registerComponent('ReactRoot', () => ReactRoot);
